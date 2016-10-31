// SerialPortDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MySerial.h"
#include "SerialPortDlg.h"
#include "afxdialogex.h"


#include "MySerialDlg.h"
#include "config.h"
// SerialPortDlg.cpp : 实现文件
//

HWND hCommWnd;
CString rcv_total;

// CSerialPortDlg 对话框

IMPLEMENT_DYNAMIC(CSerialPortDlg, CDialogEx)

CSerialPortDlg::CSerialPortDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CSerialPortDlg::IDD, pParent)
, m_iComPort(0)
, m_iComBaudRate(0)
, m_iDataBit(3)
, m_iStopBit(0)
, m_iParity(0)
, m_tempRcvCmd(_T(""))
, m_tempRcvCmdCount(0)
, m_tempRcvCmdSize(0)
, m_bBtFanetConnected(FALSE)
, m_strCurFunc(_T(""))
{

	EnableAutomation();
	m_bIsComConnect = FALSE;
}

CSerialPortDlg::~CSerialPortDlg()
{
	if (m_CommThread.m_bConnected == TRUE)
	{
		m_CommThread.ClosePort();
	}
}

void CSerialPortDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CSerialPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_COM_PORT, m_com_port);
	DDX_Control(pDX, IDC_COMBO2, m_com_rate);
	DDX_Control(pDX, IDC_COMBO3, m_com_dataBit);
	DDX_Control(pDX, IDC_COMBO4, m_com_stopBit);
	DDX_Control(pDX, IDC_COMBO5, m_com_parity);
	DDX_CBIndex(pDX, IDC_CB_COM_PORT, m_iComPort);
	DDX_CBIndex(pDX, IDC_COMBO2, m_iComBaudRate);
	DDX_CBIndex(pDX, IDC_COMBO3, m_iDataBit);
	DDX_CBIndex(pDX, IDC_COMBO4, m_iStopBit);
	DDX_CBIndex(pDX, IDC_COMBO5, m_iParity);

	DDX_Control(pDX, IDC_BTN_OPEN_PORT, m_btn_com_open);
	DDX_Control(pDX, IDC_BTN_CLOSE_PORT, m_btn_com_close);
}


BEGIN_MESSAGE_MAP(CSerialPortDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OPEN_PORT, &CSerialPortDlg::OnBnClickedBtnOpenPort)
	ON_BN_CLICKED(IDC_BTN_CLOSE_PORT, &CSerialPortDlg::OnBnClickedBtnClosePort)
	ON_MESSAGE(WM_COMM_READ, &CSerialPortDlg::OnCommRead)
	//	ON_WM_DEVICECHANGE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSerialPortDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ISerialPortDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {D360929E-EC6E-4699-BEC0-27D61BBEAE6C}
static const IID IID_ISerialPortDlg =
{ 0xD360929E, 0xEC6E, 0x4699, { 0xBE, 0xC0, 0x27, 0xD6, 0x1B, 0xBE, 0xAE, 0x6C } };

BEGIN_INTERFACE_MAP(CSerialPortDlg, CDialogEx)
	INTERFACE_PART(CSerialPortDlg, IID_ISerialPortDlg, Dispatch)
END_INTERFACE_MAP()


// CSerialPortDlg 消息处理程序


CString CSerialPortDlg::byIndexComPort(int xPort)
{
	CString PortName;
#if 1
	PortName.Format(L"\\\\.\\COM%d", xPort);
#else
	switch (xPort)
	{
	case 0:		PortName = "COM1"; 			break;
	case 1:		PortName = "COM2";			break;
	case 2:		PortName = "COM3"; 			break;
	case 3:		PortName = "COM4";			break;
	case 4:		PortName = "\\\\.\\COM5"; 	break;
	case 5:		PortName = "\\\\.\\COM6";	break;
	case 6:		PortName = "\\\\.\\COM7"; 	break;
	case 7:		PortName = "\\\\.\\COM8";	break;
	case 8:		PortName = "\\\\.\\COM9"; 	break;
	case 9:		PortName = "\\\\.\\COM10";	break;
	case 10:	PortName = "\\\\.\\COM11";	break;
	case 11:	PortName = "\\\\.\\COM12";	break;
	case 12:	PortName = "\\\\.\\COM13";	break;
	case 13:	PortName = "\\\\.\\COM14";	break;
	case 14:	PortName = "\\\\.\\COM15";	break;
	case 15:	PortName = "\\\\.\\COM16";	break;
	case 16:	PortName = "\\\\.\\COM17";	break;
	case 17:	PortName = "\\\\.\\COM18";	break;
	case 18:	PortName = "\\\\.\\COM19";	break;
	case 19:	PortName = "\\\\.\\COM20";	break;
	case 20:	PortName = "\\\\.\\COM21";	break;
	case 21:	PortName = "\\\\.\\COM22";	break;
	case 22:	PortName = "\\\\.\\COM23";	break;
	case 23:	PortName = "\\\\.\\COM24";	break;
	case 24:	PortName = "\\\\.\\COM25";	break;
	case 25:	PortName = "\\\\.\\COM26";	break;
	}
#endif
	return PortName;
}


DWORD CSerialPortDlg::byIndexBaud(int xBaud)
{
	DWORD dwBaud = CBR_9600;
	switch (xBaud)
	{
	case 0:		dwBaud = CBR_9600;		break;
	case 1:		dwBaud = CBR_19200;		break;
	case 2:		dwBaud = CBR_38400;		break;
	case 3:		dwBaud = CBR_57600;		break;
	case 4:		dwBaud = CBR_115200;	break;
	}
	return dwBaud;
}


BYTE CSerialPortDlg::byIndexData(int xData)
{
	BYTE byData = 8;
	switch (xData)
	{
	case 0:	byData = 5;			break;
	case 1:	byData = 6;			break;
	case 2:	byData = 7;			break;
	case 3:	byData = 8;			break;
	}
	return byData;
}


BYTE CSerialPortDlg::byIndexStop(int xStop)
{
	BYTE byStop = ONESTOPBIT;
	if (xStop == 0)
	{
		byStop = ONESTOPBIT;
	}
	else
	{
		byStop = TWOSTOPBITS;
	}
	return byStop;
}


BYTE CSerialPortDlg::byIndexParity(int xParity)
{
	BYTE byParity = NOPARITY;
	switch (xParity)
	{
	case 0:	byParity = NOPARITY;	break;
	case 1:	byParity = ODDPARITY;	break;
	case 2:	byParity = EVENPARITY;	break;
	}
	return byParity;
}



int CSerialPortDlg::ConvertHexChar(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else
		return (-1);
}


int CSerialPortDlg::SendAsciiData(CString inputStr)
{
	if (!m_CommThread.m_bConnected)
	{
		AfxMessageBox(L"Com Not Connect!");
		return -1;
	}
	if (inputStr.IsEmpty())
	{
		BYTE tm[2] = { 0x0d, 0x0a };
		m_CommThread.WriteComm(tm, 1);
		return -1;
	}

	rcv_total = L"";
	int nSize = inputStr.GetLength() + 2;
	BYTE *Send_buff;
	Send_buff = new BYTE[nSize];
	for (int i = 0; i < nSize - 2; i++)
	{
		Send_buff[i] = (BYTE)inputStr[i];
	};
	Send_buff[nSize - 2] = 0x0d;
	Send_buff[nSize - 1] = 0x0a;
	if (nSize != 0)
	{
		m_CommThread.WriteComm(Send_buff, nSize-1);
	}
	delete[] Send_buff;
	return nSize;
}


int CSerialPortDlg::SendHexData(CString inputStr)
{
	if (!m_CommThread.m_bConnected)
	{
		AfxMessageBox(L"Com Not Connect!");
		return -1;
	}
	if (inputStr.IsEmpty())
	{
		return -1;
	}
	//CMySerialDlg * pMainDlg = (CMySerialDlg *)this->GetParent();
	//pMainDlg->m_uartLogDlg->AddLog(L"S:" + inputStr);

	rcv_total = L"";
	int bufPos = 0;
	int datasize, bufsize, i;
	BYTE *Send_buff, byHigh, byLow;
	inputStr.Replace(L" ", L"");
	inputStr.Replace(L"\r\n", L"");
	datasize = inputStr.GetLength();

	if (datasize % 2 == 0)
	{
		bufsize = datasize;
	}
	else
	{
		bufsize = datasize - 1;
	}

	Send_buff = new BYTE[bufsize];

	for (i = 0; i < bufsize; i += 2)
	{
		byHigh = ConvertHexChar((char)inputStr[i]);
		byLow = ConvertHexChar((char)inputStr[i + 1]);
		Send_buff[bufPos++] = (byHigh << 4) | byLow;
	}

	if (bufPos != 0)
	{
		m_CommThread.WriteComm(Send_buff, bufPos);
	}

	delete[] Send_buff;
	return bufPos;
}

BOOL CSerialPortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	hCommWnd = this->m_hWnd;

#if 1
	m_com_port.ResetContent();

	i_com_list* pComItemlist = m_CommThread.comports()->update_list();
	pComItemlist->callback(&com_udpate_list_callback, &m_com_port);
	m_com_port.SetDroppedWidth(150);
	m_com_port.SetCurSel(0);
#endif



	CCommonConfig tt;
	tt.loadConfig();

	int value;
	CString val = tt.getKey(L"port");
	if (!val.IsEmpty())
	{
		value = _ttoi(val); 
		m_com_port.SetCurSel(value);
	}

	val = tt.getKey(L"rate");
	if (!val.IsEmpty())
	{
		value = _ttoi(val);
		m_com_rate.SetCurSel(value);
	}

	val = tt.getKey(L"databit");
	if (!val.IsEmpty())
	{
		value = _ttoi(val);
		m_com_dataBit.SetCurSel(value);
	}


	val = tt.getKey(L"stopbit");
	if (!val.IsEmpty())
	{
		value = _ttoi(val);
		m_com_stopBit.SetCurSel(value);
	}


	val = tt.getKey(L"parity");
	if (!val.IsEmpty())
	{
		value = _ttoi(val);
		m_com_parity.SetCurSel(value);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CSerialPortDlg::com_udpate_list_callback(void* ud, const t_com_item* t)
{
	int index = -1;
	CComboBox * combox = (CComboBox *)ud;
	c_comport* d = (c_comport*)t;
	index = combox->InsertString(-1, d->get_id_and_name());
	
	if (index >= 0)
	{
		combox->SetItemData(index, (DWORD_PTR)t);
	}
} 


void CSerialPortDlg::OnBnClickedBtnOpenPort()
{
	CString comPort;
	CString comBaudRate;
	CString comDateBit;
	CString comStopBit;
	CString comParity;

#if 1
	t_com_item* pi = (t_com_item*)(m_com_port.GetCurSel() == -1 ? 0 : m_com_port.GetItemData(m_com_port.GetCurSel()));

	m_iComPort = pi->get_i();
#else
	m_iComPort = m_com_port.GetCurSel();
	m_com_port.GetLBText(m_iComPort, comPort);
#endif
	m_iComBaudRate = m_com_rate.GetCurSel();
	m_com_rate.GetLBText(m_iComBaudRate, comBaudRate);
	m_iDataBit = m_com_dataBit.GetCurSel();
	m_com_dataBit.GetLBText(m_iDataBit, comDateBit);
	m_iStopBit = m_com_stopBit.GetCurSel();
	m_com_stopBit.GetLBText(m_iStopBit, comStopBit);
	m_iParity = m_com_parity.GetCurSel();
	m_com_parity.GetLBText(m_iParity, comParity);

	//AfxMessageBox(comPort+"\n"+comBaudRate+"\n"+comDateBit+"\n"+comStopBit+"\n"+comParity);
	m_bBtFanetConnected = FALSE;

	if (m_CommThread.m_bConnected == FALSE)
	{
		if (m_CommThread.OpenPort(byIndexComPort(m_iComPort), byIndexBaud(m_iComBaudRate), byIndexData(m_iDataBit), byIndexStop(m_iStopBit), byIndexParity(m_iParity)) == TRUE)
		{
			m_btn_com_open.EnableWindow(FALSE);
			m_bIsComConnect = TRUE;

			this->ShowWindow(SW_HIDE);
		}
		else
		{
			// port open failed
		}
	}
	else
	{
		m_btn_com_open.EnableWindow(FALSE);
		AfxMessageBox(L"Already Port open");
	}


	CCommonConfig tt;
	CString value;
	value.Format(L"%d", m_com_port.GetCurSel());
	tt.addKey(L"port", value);

	value.Format(L"%d", m_iComBaudRate);
	tt.addKey(L"rate", value);

	value.Format(L"%d", m_iDataBit);
	tt.addKey(L"databit", value);

	value.Format(L"%d", m_iStopBit);
	tt.addKey(L"stopbit", value);

	value.Format(L"%d", m_iParity);
	tt.addKey(L"parity", value);
	tt.saveConfig();
}

void CSerialPortDlg::OnBnClickedBtnClosePort()
{
	m_bIsComConnect = FALSE;
	rcv_total = L"";
#if 1
	if (m_CommThread.m_bConnected == TRUE)
	{
		m_CommThread.ClosePort();
	}
	else
	{
	}
	m_btn_com_open.EnableWindow(TRUE);

#endif
}

afx_msg LRESULT CSerialPortDlg::OnCommRead(WPARAM wParam, LPARAM lParam)
{
	BYTE buffPreProcess[2048] = { 0, };
	CString str = L"";
	int iSize = (m_CommThread.m_QueueRead).GetSize();
	BYTE aByte;

	static int type = 0;

	//m_tempRcvCmd

	CMySerialDlg * pMainDlg = (CMySerialDlg *)this->GetParent();

	for (int i = 0; i < iSize; i++)
	{
		(m_CommThread.m_QueueRead).GetByte(&aByte);
		str.Format(L"%c", aByte);
		pMainDlg->m_uartLogDlg->AddLog(str);
	}
	return 0;
}




void CSerialPortDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	OnBnClickedBtnClosePort();
	CDialogEx::OnClose();
}
