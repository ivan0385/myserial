#include "stdafx.h"

#include "CanDevice.h"



#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")


CanDevice::CanDevice(int Channel)
: m_DevType(VCI_USBCAN2) 
, m_DevIndex(0) // 第几个插入的can 盒子. 第一个为0
, m_DevChMask(Channel) // 使能那些channel bit0=1:enable channel 1,  bit1=1: enable channel 2
, m_IsDeviceOpen(false)
, m_ActiveSendChannel(Channel-1) // 从哪个channel 发送数据
{
}


CanDevice::~CanDevice()
{
}



bool CanDevice::IsDeviceOpen()
{
	return m_IsDeviceOpen;
}

bool CanDevice::TryOpenDevice()
{
	if (IsDeviceOpen())
	{
		AfxMessageBox(L"CAN已经打开了!");
		return true;
	}
	//打开设备
	if (VCI_OpenDevice(m_DevType, m_DevIndex, 0) != 1)
	{
		AfxMessageBox(L"open failed");
		return false;
	}

	VCI_INIT_CONFIG InitInfo[1];
	InitInfo->Timing0 = 0x00; // 500kbs
	InitInfo->Timing1 = 0x1c; // 500kbs
	InitInfo->Filter = 0;
	InitInfo->AccCode = 0x80000000;
	InitInfo->AccMask = 0xFFFFFFFF;
	InitInfo->Mode = 0; // 0:正常工作模式

	if (m_DevChMask & 0x1)//初始化通道1
	{
		if (VCI_InitCAN(m_DevType, m_DevIndex, 0, InitInfo) != 1)
		{
			AfxMessageBox(L"Init-CAN Channel 0 failed!");
			return false;
		}
		Sleep(100);
		if (VCI_StartCAN(m_DevType, m_DevIndex, 0) != 1)
		{
			AfxMessageBox(L"Start-CAN Channel 0 failed!");
			return false;
		}
	}
	
	if (m_DevChMask & 0x2)//初始化通道2
	{
		if (VCI_InitCAN(m_DevType, m_DevIndex, 1, InitInfo) != 1)
		{
			AfxMessageBox(L"Init-CAN Channel 1 failed!");
			return false;
		}
		Sleep(100);
		if (VCI_StartCAN(m_DevType, m_DevIndex, 1) != 1)
		{
			AfxMessageBox(L"Start-CAN Channel 1 failed!");
			return false;
		}
	}

	AfxMessageBox(L"CAN开启成功!");
	_begin_threads();

	m_IsDeviceOpen = true;
	return true;
}

bool CanDevice::TryCloseDevice()
{
	if (!IsDeviceOpen())
	{
		AfxMessageBox(L"CAN设备已关闭!");
		return true;
	}
	end_threads();

	if (VCI_CloseDevice(m_DevType, m_DevIndex) != 1)
	{
		AfxMessageBox(L"CAN Close failed！");
		return false;

	}

	AfxMessageBox(L"CAN设备已关闭!");

	m_IsDeviceOpen = false;
	return true;
}


bool CanDevice::CanSend(int iChannel, VCI_CAN_OBJ * sendBuf, int frames)
{
	if (sendBuf == nullptr)
		return false;	

	//调用动态链接库发送函数
	int flag = VCI_Transmit(m_DevType, m_DevIndex, iChannel, sendBuf, frames);//CAN message send
	if (flag<1)
	{
#if 0//def _DEBUG
		if (flag == -1)
			AfxMessageBox(L"failed- device not open\n");
		else if (flag == 0)
			AfxMessageBox(L"send error\n");
#endif
		return false;
	}

	return true;
}


bool CanDevice::CanSendNormalData(ST_PACKET packetBuf) // CAN2.0A data frame
{
	CAN_SEND_DATA_PACKETS packet;
	VCI_CAN_OBJ sendBuf[1] = { 0, };
	sendBuf->ExternFlag = 0;
	sendBuf->DataLen = 8;
	sendBuf->RemoteFlag = 0;
	sendBuf->ID = packetBuf.id;
	sendBuf->SendType = 0; // 0: 失败重复, 1:单次发送
	for (int i = 0; i<8; i++)
		sendBuf->Data[i] = packetBuf.data[i];
	packet.data = sendBuf[0];
	packet.enable = true;
	packet.msInterval = packetBuf.tmInterval;

// add to write list
	_snd_lock.lock();
	if (packet.msInterval>10)
	{
		std::list<CAN_SEND_DATA_PACKETS>::iterator pack;
		for (pack = _SendList.begin(); pack != _SendList.end();)
		{
			if (packetBuf.id == pack->data.ID)
				_SendList.erase(pack++);
			else
				pack++;
		}
	}
	_SendList.push_back(packet);
	_snd_lock.unlock();
	return false;
}

bool CanDevice::_begin_threads()
{
	thread_helper_context* pctx = nullptr;

	// 开启读线程
	_thread_read.hEventToBegin = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
	_thread_read.hEventToExit = ::CreateEvent(nullptr, TRUE, FALSE, nullptr);

	pctx = new thread_helper_context;
	pctx->that = this;
	pctx->which = thread_helper_context::e_which::kRead;
	_thread_read.hThread = (HANDLE)::_beginthreadex(nullptr, 0, thread_helper, pctx, 0, nullptr);

	if (!_thread_read.hEventToBegin || !_thread_read.hEventToExit || !_thread_read.hThread)
	{
		::MessageBox(NULL, L"应用程序初始化失败, 即将退出!", NULL, MB_ICONHAND);
		::exit(1);
	}

	// 开启写线程
	_thread_write.hEventToBegin = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
	_thread_write.hEventToExit = ::CreateEvent(nullptr, TRUE, FALSE, nullptr);

	pctx = new thread_helper_context;
	pctx->that = this;
	pctx->which = thread_helper_context::e_which::kWrite;
	_thread_write.hThread = (HANDLE)::_beginthreadex(nullptr, 0, thread_helper, pctx, 0, nullptr);

	if (!_thread_write.hEventToBegin || !_thread_write.hEventToExit || !_thread_write.hThread)
	{
		::MessageBox(NULL, L"应用程序初始化失败, 即将退出!", NULL, MB_ICONHAND);
		::exit(1);
	}


	begin_threads();

	return true;
}


unsigned int __stdcall CanDevice::thread_helper(void* pv)
{
	auto pctx = reinterpret_cast<thread_helper_context*>(pv);
	auto comm = pctx->that;
	auto which = pctx->which;

	delete pctx;

	switch (which)
	{
	case thread_helper_context::e_which::kRead:
		return comm->thread_read();
	case thread_helper_context::e_which::kWrite:
		return comm->thread_write();
	default:
		return 1;
	}
}

unsigned int CanDevice::thread_read()
{
	debug_out(("[读线程] 就绪\n"));
	::WaitForSingleObject(_thread_read.hEventToBegin, INFINITE);

	debug_out(("[读线程] 开始工作...\n"));
	if (!IsDeviceOpen())
	{
		debug_out(("[读线程] 设备没有打开, 退出中...\n"));
		::ResetEvent(_thread_read.hEventToExit);
		return 0;
	}
	
	HANDLE handles[1];
	handles[0] = _thread_read.hEventToExit;
	debug_out(("[读线程] start!\n"));

_get_packet:
	switch (::WaitForMultipleObjects(_countof(handles), handles, FALSE, 1))
	{
	case WAIT_OBJECT_0 + 0:
		debug_out(("[读线程] 收到退出事件!\n"));
		::ResetEvent(_thread_read.hEventToExit);
		return 0;
	}

	int NumValue;	
	VCI_CAN_OBJ pCanObj[200];

	for (int kCanIndex = 0; kCanIndex<2; kCanIndex++)
	{
		//调用动态链接看接收函数
		NumValue = VCI_Receive(m_DevType, m_DevIndex, kCanIndex, pCanObj, 200, 0);
		//接收信息列表显示
		call_data_receivers(pCanObj, NumValue);
	}
	Sleep(10);	
	goto _get_packet;
}


unsigned int CanDevice::thread_write()
{
	DWORD icount;

	DWORD t1=0,t2=0,t3=0;
	bool bTm100 = false;
	bool bTm20 = false;

_wait_for_work:
	debug_out(("[写线程] 就绪\n"));
	::WaitForSingleObject(_thread_write.hEventToBegin, INFINITE);

	debug_out(("[写线程] 开始工作...\n"));
	if (!IsDeviceOpen())
	{
		debug_out(("[写线程] 没有工作, 退出中...\n"));
		::SetEvent(_thread_write.hEventToExit);
		return 0;
	}

	VCI_CAN_OBJ *sendBuf = (VCI_CAN_OBJ *)malloc(sizeof(VCI_CAN_OBJ)* 48);
	HANDLE handles[1];
	handles[0] = _thread_write.hEventToExit;
	debug_out(("[写线程] 取数据包中...\n"));

_get_packet:

	while (timeGetTime() - t3 < 10)
	{
		t3 = timeGetTime();
		Sleep(1);
	}

	if (timeGetTime() - t1 > 100)
	{
		t1 = timeGetTime();
		bTm100 = true;
	}
	if (timeGetTime() - t2 > 20)
	{
		t2 = timeGetTime();
		bTm20 = true;
	}
	switch (::WaitForMultipleObjects(_countof(handles), handles, FALSE, 1))
	{
	case WAIT_OBJECT_0 + 0:
		debug_out(("[写线程] 收到退出事件!\n"));
		::ResetEvent(_thread_write.hEventToExit);
		free(sendBuf);
		return 0;
	}

	icount = 0;
	std::list<CAN_SEND_DATA_PACKETS>::iterator pack;
	_snd_lock.lock();
	for (pack = _SendList.begin(); pack != _SendList.end();)
	{
		if (pack->enable)
		{
			if (pack->msInterval == 0)
				sendBuf[icount++] = pack->data;
			else if (bTm20 && pack->msInterval == 20)
				sendBuf[icount++] = pack->data;
			else if (bTm100 && pack->msInterval == 100)
				sendBuf[icount++] = pack->data;
		}
		if (pack->msInterval < 10 || !pack->enable)
		{
			pack = _SendList.erase(pack);
		}
		else
			pack++;
	}
	_snd_lock.unlock();

	if (icount > 0)
	{
		CanSend(m_ActiveSendChannel, sendBuf, icount);
	}
	bTm100 = false;
	bTm20 = false;
	
	goto _get_packet;
}

bool CanDevice::begin_threads()
{
	::ResetEvent(_thread_read.hEventToExit);
	::ResetEvent(_thread_write.hEventToExit);

	::SetEvent(_thread_read.hEventToBegin);
	::SetEvent(_thread_write.hEventToBegin);

	return true;
}

bool CanDevice::end_threads()
{
	::ResetEvent(_thread_read.hEventToBegin);
	::ResetEvent(_thread_write.hEventToBegin);

	::SetEvent(_thread_read.hEventToExit);
	// 在读写线程退出之前, 两个end均为激发状态
	// 必须等到两个线程均退出工作状态才能有其它操作
	debug_out(("等待 [读线程] 结束...\n"));
	while (::WaitForSingleObject(_thread_read.hEventToExit, 0) == WAIT_OBJECT_0);


	::SetEvent(_thread_write.hEventToExit);
	debug_out(("等待 [写线程] 结束...\n"));
	while (::WaitForSingleObject(_thread_write.hEventToExit, 0) == WAIT_OBJECT_0);
	
	return true;
}

void CanDevice::call_data_receivers(const VCI_CAN_OBJ * ba, int cb)
{
	_data_receiver_lock.lock();
	for (int i = 0; i < _data_receivers.size(); i++)
	{
		_data_receivers[i]->receive(ba, cb);
	}
	_data_receiver_lock.unlock();
}

void CanDevice::remove_data_receiver(i_data_receiver* receiver)
{
	_data_receiver_lock.lock();
	_data_receivers.remove(receiver);
	_data_receiver_lock.unlock();

}

void CanDevice::add_data_receiver(i_data_receiver* receiver)
{
	_data_receiver_lock.lock();
	_data_receivers.add(receiver);
	_data_receiver_lock.unlock();
}