#pragma once
#include <list>
#include "ControlCAN.h"

#include "CanMatrix.h"
#include "wj_utils.h"

#ifdef _DEBUG
#define debug_out(x) printf##x
#else
#define debug_out(x) 
#endif


// 数据接收器接口: 串口在接收到数据后调用所有的接收器
class i_data_receiver
{
public:
	// 数据接收函数, 读线程接收到数据时调用此函数
	// ba指向的内容不应该被更改!
	virtual void receive(const VCI_CAN_OBJ* ba, int cb) = 0;
	virtual void reset_buffer() = 0;
};

class CanDevice
{
public:
	CanDevice(int Channel=1);
	~CanDevice();
	int m_DevType;
	int m_DevIndex;
	int m_DevChMask;
	int m_ActiveSendChannel;
	bool m_IsDeviceOpen;
	bool TryOpenDevice();
	bool IsDeviceOpen();
	bool TryCloseDevice();
	bool CanSend(int iChannel, VCI_CAN_OBJ * sendBuf, int frames);
	bool CanSendNormalData(ST_PACKET packetBuf);

	bool begin_threads();
	bool end_threads();

	// 数据接收器
public:
	void add_data_receiver(i_data_receiver* receiver);
	void remove_data_receiver(i_data_receiver* receiver);
	void call_data_receivers(const VCI_CAN_OBJ* ba, int cb);
	c_ptr_array<i_data_receiver>	_data_receivers;
	c_critical_locker	_data_receiver_lock;

private:
	struct thread_helper_context
	{
		CanDevice* that;
		enum class e_which
		{
			kRead,
			kWrite,
		};
		e_which which;
	};
	struct thread_state
	{
		HANDLE hThread;
		HANDLE hEventToBegin;
		HANDLE hEventToExit;
	};
	unsigned int thread_read();
	unsigned int thread_write();
	static unsigned int __stdcall thread_helper(void* pv);

	thread_state	_thread_read;
	thread_state	_thread_write;
public:
	bool _begin_threads();

	typedef struct
	{
		int msInterval; // 0:发送一次, 100ms:100ms循环一次
		bool enable;
		VCI_CAN_OBJ data;
	}CAN_SEND_DATA_PACKETS;
	std::list<CAN_SEND_DATA_PACKETS> _SendList;
	c_critical_locker _snd_lock;		// 多线程锁
};

