#include "stdafx.h"
#include "CommThread.h"
#include <SetupAPI.h>
#include <WinIoCtl.h>

#pragma comment (lib,"setupapi.lib")


extern HWND hCommWnd;



void CQueue::Clear()
{
	m_iHead = m_iTail =0;
	memset(buff,0,BUFF_SIZE);
}
CQueue::CQueue()
{
	Clear();
}
int CQueue::GetSize()
{
	return (m_iHead - m_iTail + BUFF_SIZE) % BUFF_SIZE;
}
BOOL CQueue::PutByte(BYTE b)
{
	if(GetSize() == (BUFF_SIZE-1)) return FALSE;
	buff[m_iHead++] =b;
	m_iHead %= BUFF_SIZE;
	return TRUE;
}
BOOL CQueue::GetByte(BYTE *pb)
{
	if(GetSize() == 0) return FALSE;
	*pb = buff[m_iTail++];
	m_iTail %= BUFF_SIZE;
	return TRUE;
}



//////////////////////////////////////////////////////////////////////////
CString c_comport::get_id_and_name() const
{
	CString comName;
	comName.Format(L"COM%-13d\t\t",_i);
	comName.Append(_s);
	return comName;
}

//////////////////////////////////////////////////////////////////////////
i_com_list* c_comport_list::update_list()
{
	HDEVINFO hDevInfo = INVALID_HANDLE_VALUE;
	SP_DEVINFO_DATA spdata = { 0 };
	GUID guid = GUID_DEVINTERFACE_COMPORT;

	empty();

	hDevInfo = SetupDiGetClassDevs(&guid, 0, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		return this;
	}

	spdata.cbSize = sizeof(spdata);
	for (int i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &spdata); i++)
	{
		wchar_t buff[1024] = { 0, };
		if (SetupDiGetDeviceRegistryProperty(hDevInfo, &spdata, SPDRP_FRIENDLYNAME, NULL,
			PBYTE(buff), _countof(buff), NULL))
		{
			// Prolific com port (COMxx)
			CString tmp(buff);
			int idx = tmp.Find(L"(COM");
			if (idx >= 0)
			{
				int id = _wtoi(tmp.Right(tmp.GetLength() - idx - 4));

				tmp = tmp.SpanExcluding(L"(COM");
				add(c_comport(id, tmp));
			}

			
		}
	}
	SetupDiDestroyDeviceInfoList(hDevInfo);

	return this;
}

void CCommThread::init()
{
	CString aBaudRate[] = { L"110", L"300", L"600", L"1200", L"2400", L"4800", L"9600", L"14400", L"19200", L"38400", L"57600", L"115200", L"128000", L"256000", NULL };
	static DWORD iBaudRate[] = { CBR_110, CBR_300, CBR_600, CBR_1200, CBR_2400, CBR_4800, CBR_9600, CBR_14400, CBR_19200, CBR_38400, CBR_57600, CBR_115200, CBR_128000, CBR_256000 };
	CString aParity[] = { L"无", L"奇校验", L"偶校验", L"标记", L"空格", NULL };
	static BYTE iParity[] = { NOPARITY, ODDPARITY, EVENPARITY, MARKPARITY, SPACEPARITY };
	CString aStopBit[] = { L"1位", L"1.5位", L"2位", NULL };
	static BYTE iStopBit[] = { ONESTOPBIT, ONE5STOPBITS, TWOSTOPBITS };
	CString aDataSize[] = { L"8位", L"7位", L"6位", L"5位", NULL };
	static BYTE iDataSize[] = { 8, 7, 6, 5 };

	for (int i = 0; !aBaudRate[i].IsEmpty(); i++)
		_baudrate_list.add(t_com_item(iBaudRate[i], aBaudRate[i]));
	for (int i = 0; !aParity[i].IsEmpty(); i++)
		_parity_list.add(t_com_item(iParity[i], aParity[i]));
	for (int i = 0; !aStopBit[i].IsEmpty(); i++)
		_stopbit_list.add(t_com_item(iStopBit[i], aStopBit[i]));
	for (int i = 0; !aDataSize[i].IsEmpty(); i++)
		_databit_list.add(t_com_item(iDataSize[i], aDataSize[i]));

	_comport_list.update_list();
}

CCommThread::CCommThread(void)
{
	init();
	m_bConnected = FALSE;
}


CCommThread::~CCommThread(void)
{
}

BOOL CCommThread::OpenPort(CString strPortName, 
						   DWORD dwBaud, BYTE byData, BYTE byStop, BYTE byParity )
{
	COMMTIMEOUTS	timeouts;
	DCB				dcb;
	DWORD			dwThreadID;

	// overlapped structure
	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	//--> Read 
	if ( !(m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) ) 	
	{
		return FALSE;
	}


	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	//--> Write 
	if (! (m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
	{
		return FALSE;
	}

	//--> 
	m_sPortName = strPortName;

	//--> RS 232
	//\\\\?\\COM10 端口名字com10以上应添加"\\?\"
	m_hComm = CreateFile(m_sPortName, 
		GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
		NULL);


	//--> 
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		AfxMessageBox(L"Fail Port Open");
		return FALSE;
	}

	
	// EV_RXCHAR event 
	SetCommMask( m_hComm, EV_RXCHAR);	

	// InQueue, OutQueue 
	SetupComm( m_hComm, BUFF_SIZE, BUFF_SIZE);	

	// 
	PurgeComm( m_hComm,					
		PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	// timeout
	timeouts.ReadIntervalTimeout = 0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;

	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_9600 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;

	SetCommTimeouts( m_hComm, &timeouts);

	// dcb 
	dcb.DCBlength = sizeof(DCB);

	//-->
	GetCommState( m_hComm, &dcb);	

	//-->
	dcb.BaudRate = dwBaud;


	//--> Data 8 Bit
	dcb.ByteSize = byData;

	//--> Noparity
	dcb.Parity = byParity;

	//--> 1 Stop Bit
	dcb.StopBits = byStop;


	//--> 
	if( !SetCommState( m_hComm, &dcb) )	
	{
		return FALSE;
	}


	// 
	m_bConnected = TRUE;

	//--> 
	m_hThreadWatchComm = CreateThread( NULL, 0, 
		(LPTHREAD_START_ROUTINE)ThreadWatchComm, 
		this, 0, &dwThreadID);

	//-->
	if (! m_hThreadWatchComm)
	{
		ClosePort();
		return FALSE;
	}
	check = FALSE;

	return TRUE;
}

void CCommThread::ClosePort()
{
	m_bConnected = FALSE;

	SetCommMask( m_hComm, 0);

	PurgeComm( m_hComm,	PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);

	CloseHandle(m_hComm);
}

DWORD CCommThread::WriteComm(BYTE *pBuff, DWORD nToWrite)
{
	DWORD	dwWritten, dwError, dwErrorFlags;
	COMSTAT	comstat;

	BYTE buffWrite[1024]={0,};
	DWORD writeSize = nToWrite;
	memcpy(buffWrite,pBuff,nToWrite);

	if( !m_bConnected )		
	{
		return 0;
	}

	if( !WriteFile( m_hComm, buffWrite, writeSize, &dwWritten, &m_osWrite))
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			while (! GetOverlappedResult( m_hComm, &m_osWrite, &dwWritten, TRUE))
			{
				dwError = GetLastError();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError( m_hComm, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError( m_hComm, &dwErrorFlags, &comstat);
		}
	}

	return dwWritten;
}

DWORD CCommThread::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	DWORD	dwRead,dwError, dwErrorFlags;
	COMSTAT comstat;

	//--- system queue
	ClearCommError( m_hComm, &dwErrorFlags, &comstat);

	dwRead = comstat.cbInQue;
	if(dwRead > 0)
	{
		if( !ReadFile( m_hComm, pBuff, nToRead, &dwRead, &m_osRead) )
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				//--------- timeouts
				while (! GetOverlappedResult( m_hComm, &m_osRead, &dwRead, TRUE))
				{
					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError( m_hComm, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError( m_hComm, &dwErrorFlags, &comstat);
			}
		}
	}

	return dwRead;
}


DWORD ThreadWatchComm(CCommThread* pComm)
{
	DWORD           dwEvent;
	OVERLAPPED      os;
	BOOL            bOk = TRUE;
	BYTE            buff[204800];
	DWORD           dwRead;

	// Event, OS
	memset( &os, 0, sizeof(OVERLAPPED));

	if( !(os.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL)) )
	{
		bOk = FALSE;
	}

	if( !SetCommMask( pComm->m_hComm, EV_RXCHAR) )
	{
		bOk = FALSE;
	}

	if( !bOk )
	{
		AfxMessageBox(L"Error while creating ThreadWatchComm, " + pComm->m_sPortName);
		return FALSE;
	}

	while (pComm ->m_bConnected)
	{
		dwEvent = 0;

		WaitCommEvent( pComm->m_hComm, &dwEvent, NULL);

		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			do
			{
				dwRead = pComm->ReadComm(buff, 1024);
				if(BUFF_SIZE - pComm->m_QueueRead.GetSize() > (int)dwRead)
				{
					for( WORD i = 0; i < dwRead; i++ )
					{
						pComm->m_QueueRead.PutByte(buff[i]);
					}
				}
				else
				{
					AfxMessageBox(L"buff full");
				}
			}while(dwRead);
			::PostMessage(hCommWnd, WM_COMM_READ, 0, 0 );
		}
		Sleep(0);
	}

	CloseHandle( os.hEvent);

	pComm->m_hThreadWatchComm = NULL;

	return TRUE;
}
