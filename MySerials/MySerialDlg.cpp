
// MySerialDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MySerial.h"
#include "afxdialogex.h"



#include "MySerialDlg.h"

#include "CanMatrix.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMySerialDlg 对话框



CMySerialDlg::CMySerialDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMySerialDlg::IDD, pParent)
	, m_isinit(0)
	, m_speed(0)
	, m_angle(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMySerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ED_SND1, m_edit_s1);
	DDX_Control(pDX, IDC_ED_SND2, m_edit_s2);
	DDX_Control(pDX, IDC_ED_SND3, m_edit_s3);
	DDX_Control(pDX, IDC_ED_SND4, m_edit_s4);
	DDX_Control(pDX, IDC_ED_SND5, m_edit_s5);
	DDX_Control(pDX, IDC_ED_SND6, m_edit_s6);
	DDX_Control(pDX, IDC_ED_SND7, m_edit_s7);
	DDX_Control(pDX, IDC_ED_SND8, m_edit_s8);
	DDX_Control(pDX, IDC_ED_SND9, m_edit_s9);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tab_main);
	DDX_Text(pDX, IDC_EDIT_SPD, m_speed);
	DDV_MinMaxInt(pDX, m_speed, 0, 255);
	DDX_Text(pDX, IDC_EDIT_ANGLE, m_angle);
	DDV_MinMaxInt(pDX, m_angle, -55, +55);
	DDX_Control(pDX, IDC_EDIT_SPD, m_edit_speed);
	DDX_Control(pDX, IDC_EDIT_ANGLE, m_edit_angle);
	DDX_Control(pDX, IDC_ED_SND10, m_edit_s10);
}

BEGIN_MESSAGE_MAP(CMySerialDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_CONNECTION_NEWCONNECTION, &CMySerialDlg::OnConnectionNewconnection)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_NFS, &CMySerialDlg::OnBnClickedBtnNfs)
	ON_BN_CLICKED(IDC_BTN_CPSVP, &CMySerialDlg::OnBnClickedBtnCpsvp)
	ON_BN_CLICKED(IDC_BTN_CPBIN, &CMySerialDlg::OnBnClickedBtnCpbin)
	ON_BN_CLICKED(IDC_BTN_CPRADIO, &CMySerialDlg::OnBnClickedBtnCpradio)
	ON_BN_CLICKED(IDC_REBOOT, &CMySerialDlg::OnBnClickedReboot)
	ON_BN_CLICKED(IDC_BTN_RVS1, &CMySerialDlg::OnBnClickedBtnRvs1)
	ON_BN_CLICKED(IDC_BTN_TURNLEFT1, &CMySerialDlg::OnBnClickedBtnTurnleft1)
	ON_BN_CLICKED(IDC_BTN_TURNRGHT1, &CMySerialDlg::OnBnClickedBtnTurnrght1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SPEED, &CMySerialDlg::OnDeltaposSpinSpeed)
	ON_BN_CLICKED(IDC_BTN_S1, &CMySerialDlg::OnBnClickedBtnS1)
	ON_BN_CLICKED(IDC_BTN_S2, &CMySerialDlg::OnBnClickedBtnS2)
	ON_BN_CLICKED(IDC_BTN_S3, &CMySerialDlg::OnBnClickedBtnS3)
	ON_BN_CLICKED(IDC_BTN_S4, &CMySerialDlg::OnBnClickedBtnS4)
	ON_BN_CLICKED(IDC_BTN_S5, &CMySerialDlg::OnBnClickedBtnS5)
	ON_BN_CLICKED(IDC_BTN_S6, &CMySerialDlg::OnBnClickedBtnS6)
	ON_BN_CLICKED(IDC_BTN_S7, &CMySerialDlg::OnBnClickedBtnS7)
	ON_BN_CLICKED(IDC_BTN_S8, &CMySerialDlg::OnBnClickedBtnS8)
	ON_BN_CLICKED(IDC_BTN_S9, &CMySerialDlg::OnBnClickedBtnS9)
	ON_BN_CLICKED(IDC_BTN_RADAR, &CMySerialDlg::OnBnClickedBtnRadar)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CMySerialDlg::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDC_BTN_EOL, &CMySerialDlg::OnBnClickedBtnEol)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CMySerialDlg::OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_BUTTON_IGN, &CMySerialDlg::OnBnClickedButtonIgn)
	ON_BN_CLICKED(IDC_BUTTON_3D, &CMySerialDlg::OnBnClickedButton3d)
	ON_BN_CLICKED(IDC_BUTTON3, &CMySerialDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMySerialDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMySerialDlg::OnBnClickedButton5)
	ON_COMMAND(ID_CONNECTION_32772, &CMySerialDlg::OnConnection32772)
	ON_BN_CLICKED(IDC_BTN_CPSVP2, &CMySerialDlg::OnBnClickedBtnCpsvp2)
END_MESSAGE_MAP()


// CMySerialDlg 消息处理程序

BOOL CMySerialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码


	GetClientRect(&m_rect);
	// init tab
	CRect tabRect;
	m_tab_main.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 3;
	tabRect.top += 23;
	tabRect.bottom -= 3;
	m_tab_main.InsertItem(0, L"Uart Log");
	

	// 初始化 can盒子
	m_canDevice = new CanDevice(2);
	m_canData = new CanMatrix;


	// init serial port dlg
	if (m_serialComDlg == NULL)
	{
		m_serialComDlg = new CSerialPortDlg;
		m_serialComDlg->Create(IDD_COM_SETTING);
	}
	m_serialComDlg->ShowWindow(SW_HIDE);
	m_serialComDlg->CenterWindow();


	// init uart dlg
	m_uartLogDlg = new CUartLogDlg;	
	m_uartLogDlg->Create(IDD_DIALOG_LOG, GetDlgItem(IDC_TAB_MAIN));
	m_uartLogDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_uartLogDlg->ShowWindow(SW_SHOW);

	// init can dlg
	if (m_canDlg == NULL)
	{
		m_canDlg = new CCanDialog;
		m_canDlg->Create(IDD_DIALOG_CAN);
	}
	m_canDlg->ShowWindow(SW_SHOW);
	m_canDlg->CenterWindow();

	this->ShowWindow(SW_HIDE);



	m_edit_s1.SetWindowTextW(L"cd /media/sda1/pict* && ./pic.sh");
	m_edit_s2.SetWindowTextW(L"cp -f /media/sda1/video_mgr.xml /svp/etc/zm/params/video_source/");
	m_edit_s3.SetWindowTextW(L"rm -rf /svp/etc/zm/cache && sync");
	m_edit_s4.SetWindowTextW(L"wjtest touchkey 465 130"); 
	m_edit_s8.SetWindowTextW(L"flash_erase / dev / mtd6 0 0");
	m_isinit = 1;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMySerialDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMySerialDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMySerialDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMySerialDlg::OnConnectionNewconnection()
{
	m_serialComDlg->ShowWindow(SW_SHOW);
	m_serialComDlg->CenterWindow();
}


void CMySerialDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_serialComDlg->DestroyWindow();
	delete m_serialComDlg;
}


void CMySerialDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码

	ChangeSize(IDC_TAB_MAIN,cx,cy);
	GetClientRect(&m_rect);

}

void CMySerialDlg::ChangeSize(UINT nID, int x, int y)  //nID为控件ID，x,y分别为对话框的当前长和宽
{
	CWnd *pWnd;
	pWnd = GetDlgItem(nID);
	if (pWnd != NULL)     //判断是否为空，因为在窗口创建的时候也会调用OnSize函数，但是此时各个控件还没有创建，Pwnd为空
	{
		CRect rec;
		pWnd->GetWindowRect(&rec);  //获取控件变化前的大小
		ScreenToClient(&rec);   //将控件大小装换位在对话框中的区域坐标
		//rec.left = rec.left*x / m_rect.Width();  //按照比例调整空间的新位置
		//rec.top = rec.top*y / m_rect.Height();
		rec.bottom = rec.bottom*y / m_rect.Height();
		rec.right = rec.right*x / m_rect.Width();
		pWnd->MoveWindow(rec);   //伸缩控件

		// init tab
		CRect tabRect;
		m_tab_main.GetClientRect(&tabRect);
		tabRect.left += 1;
		tabRect.right -= 3;
		tabRect.top += 23;
		tabRect.bottom -= 3;
		m_uartLogDlg->SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);

		m_edit_s10.SetWindowPos(NULL, rec.left, tabRect.top + tabRect.Height() + 10, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	}
}


void CMySerialDlg::OnBnClickedBtnNfs()
{
	m_serialComDlg->SendAsciiData(L"root");
	Sleep(100);
	m_serialComDlg->SendAsciiData(L"adas-ab01");
	Sleep(200);
	m_serialComDlg->SendAsciiData(L". /svp/etc/env_setup.sh && cd /nfs && . nfs.sh");
}


void CMySerialDlg::OnBnClickedBtnCpsvp()
{
	m_serialComDlg->SendAsciiData(L"cd /nfs && ./mycpsvp.sh");
}


void CMySerialDlg::OnBnClickedBtnCpbin()
{
	m_serialComDlg->SendAsciiData(L"cd /nfs && ./mycpbin.sh");
}


void CMySerialDlg::OnBnClickedBtnCpradio()
{
	m_serialComDlg->SendAsciiData(L"cd /nfs/share && cp radio* /storage/update/");
}


void CMySerialDlg::OnBnClickedReboot()
{
	m_serialComDlg->SendAsciiData(L"reboot -f");
}


void CMySerialDlg::OnBnClickedBtnRvs1()
{
	CButton* btn = (CButton*)this->GetDlgItem(IDC_BTN_RVS1);
	CString text;
	btn->GetWindowText(text);
	if (text.Find(L"1")>0)
	{
		m_serialComDlg->SendAsciiData(L"wjtest reverse 0");
		btn->SetWindowTextW(L"Reverse 0");
	}
	else
	{
		m_serialComDlg->SendAsciiData(L"wjtest reverse 1");
		btn->SetWindowTextW(L"Reverse 1");
	}

}

void CMySerialDlg::OnBnClickedBtnTurnleft1()
{
	CButton* btn = (CButton*)this->GetDlgItem(IDC_BTN_TURNLEFT1);
	CString text;
	btn->GetWindowText(text);
	if (text.Find(L"1")>0)
	{
		m_serialComDlg->SendAsciiData(L"wjtest turnleft 0");
		btn->SetWindowTextW(L"TurnLeft 0");
	}
	else
	{
		m_serialComDlg->SendAsciiData(L"wjtest turnleft 1");
		btn->SetWindowTextW(L"TurnLeft 1");
	}
}

void CMySerialDlg::OnBnClickedBtnTurnrght1()
{
	CButton* btn = (CButton*)this->GetDlgItem(IDC_BTN_TURNRGHT1);
	CString text;
	btn->GetWindowText(text);
	if (text.Find(L"1")>0)
	{
		m_serialComDlg->SendAsciiData(L"wjtest turnright 0");
		btn->SetWindowTextW(L"TurnRight 0");
	}
	else
	{
		m_serialComDlg->SendAsciiData(L"wjtest turnright 1");
		btn->SetWindowTextW(L"TurnRight 1");
	}
}


void CMySerialDlg::OnBnClickedButtonIgn()
{	
	CButton* btn = (CButton*)this->GetDlgItem(IDC_BUTTON_IGN);
	CString text;
	btn->GetWindowText(text);
	if (text.Find(L"On")>0)
	{
		m_serialComDlg->SendAsciiData(L"wjtest ign 0");
		btn->SetWindowTextW(L"IGN Off");
	}
	else
	{
		m_serialComDlg->SendAsciiData(L"wjtest ign 2");
		btn->SetWindowTextW(L"IGN On");
	}
}




void CMySerialDlg::OnBnClickedButton3d()
{	
	CButton* btn = (CButton*)this->GetDlgItem(IDC_BUTTON_3D);
	CString text;
	btn->GetWindowText(text);
	if (text.Find(L"On")>0)
	{
		m_serialComDlg->SendAsciiData(L"wjtest setting 3 0 0 0");
		btn->SetWindowTextW(L"3D Off");
	}
	else
	{
		m_serialComDlg->SendAsciiData(L"wjtest setting 3 1 1 0");
		btn->SetWindowTextW(L"3D On");
	}
}



void CMySerialDlg::OnDeltaposSpinSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString tmp;
	CString tmp1;
	// TODO:  在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == 1)
	{
		m_speed--;
	}
	else if (pNMUpDown->iDelta == -1)
	{
		m_speed++;
	}

	tmp.Format(L"wjtest speed %d", m_speed);
	tmp1.Format(L"%d", m_speed);

	m_edit_speed.SetWindowTextW(tmp1);

	m_serialComDlg->SendAsciiData(tmp);

	*pResult = 0;
}


void CMySerialDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString tmp;
	CString tmp1;
	// TODO:  在此添加控件通知处理程序代码
	if (pNMUpDown->iDelta == 1)
	{
		m_angle--;
	}
	else if (pNMUpDown->iDelta == -1)
	{
		m_angle++;
	}

	tmp.Format(L"wjtest angle %d", m_angle);
	tmp1.Format(L"%d", m_angle);

	m_edit_angle.SetWindowTextW(tmp1);

	m_serialComDlg->SendAsciiData(tmp);

	*pResult = 0;
}

void CMySerialDlg::OnBnClickedBtnS1()
{
	CString tmp;
	m_edit_s1.GetWindowTextW(tmp);
	m_serialComDlg->SendAsciiData(tmp);
}


void CMySerialDlg::OnBnClickedBtnS2()
{
	CString tmp;
	m_edit_s2.GetWindowTextW(tmp);
	m_serialComDlg->SendAsciiData(tmp);
}


void CMySerialDlg::OnBnClickedBtnS3()
{
	CString tmp;
	m_edit_s3.GetWindowTextW(tmp);
	m_serialComDlg->SendAsciiData(tmp);
}


void CMySerialDlg::OnBnClickedBtnS4()
{
	CString tmp;
	m_edit_s4.GetWindowTextW(tmp);
	m_serialComDlg->SendAsciiData(tmp);
}


void CMySerialDlg::OnBnClickedBtnS5()
{
	CString tmp;
	m_edit_s5.GetWindowTextW(tmp);
	m_serialComDlg->SendAsciiData(tmp);
}


void CMySerialDlg::OnBnClickedBtnS6()
{
	CString tmp;
	m_edit_s6.GetWindowTextW(tmp);
	m_serialComDlg->SendAsciiData(tmp);
}


void CMySerialDlg::OnBnClickedBtnS7()
{
	CString tmp;
	m_edit_s7.GetWindowTextW(tmp);
	m_serialComDlg->SendAsciiData(tmp);
}


void CMySerialDlg::OnBnClickedBtnS8()
{
	CString tmp;
	m_edit_s8.GetWindowTextW(tmp);
	m_serialComDlg->SendAsciiData(tmp);
}


void CMySerialDlg::OnBnClickedBtnS9()
{
	CString tmp;
	m_edit_s9.GetWindowTextW(tmp);
	m_serialComDlg->SendAsciiData(tmp);
}


void CMySerialDlg::OnBnClickedBtnRadar()
{
	m_edit_s9.SetWindowTextW(L"wjtest radar 12 0 0 0 2 2 2 2 2 2 2 2 4");
}


void CMySerialDlg::OnBnClickedBtnSetting()
{
	m_edit_s9.SetWindowTextW(L"wjtest setting 3 1 1 0");
}


void CMySerialDlg::OnBnClickedBtnEol()
{
	m_edit_s9.SetWindowTextW(L"wjtest eol 1");
}



void CMySerialDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}





void CMySerialDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	m_canDevice->TryOpenDevice();

	m_canData->setBcm1_Ign(BCM1_IGN_START);
	m_canDevice->CanSendNormalData(m_canData->setBcm1_lamp(BCM1_LAMP_TURNLEFT));
}


void CMySerialDlg::OnBnClickedButton4()
{
	m_canDevice->TryOpenDevice();

	m_canDevice->CanSendNormalData(m_canData->setBcm1_Ign(BCM1_IGN_OFF));
}


void CMySerialDlg::OnBnClickedButton5()
{

	m_canDevice->TryCloseDevice();
}


void CMySerialDlg::OnConnection32772()
{
	m_canDlg->ShowWindow(SW_SHOW);
}


void CMySerialDlg::OnBnClickedBtnCpsvp2()
{
	m_serialComDlg->SendAsciiData(L"rm -rf /svp && sync && mkdir /svp && tar -zxvf /media/sda1/svp.bin -C/svp && sync && reboot -f");
}


BOOL CMySerialDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		{
			if (GetFocus() == GetDlgItem(IDC_ED_SND10))
			{
				CString temp;
				m_edit_s10.GetWindowText(temp);
				m_serialComDlg->SendAsciiData(temp);
				m_edit_s10.SetWindowText(L"");
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
