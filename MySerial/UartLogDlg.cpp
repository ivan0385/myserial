// UartLogDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "MySerial.h"
#include "UartLogDlg.h"
#include "afxdialogex.h"


#include "MySerialDlg.h"

// CUartLogDlg 对话框

IMPLEMENT_DYNAMIC(CUartLogDlg, CDialogEx)

CUartLogDlg::CUartLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUartLogDlg::IDD, pParent)
	, m_serialComDlg(NULL)
	, m_stop_refresh(0)
	, m_str_newLine(_T(""))
	, m_pos_find(0)
{
	EnableAutomation();
}

CUartLogDlg::~CUartLogDlg()
{
}

void CUartLogDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CUartLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_richEdit);
	DDX_Control(pDX, IDC_BTN_STOPSTART, m_btn_stopstart);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_edit_search);
	DDX_Control(pDX, IDC_BUTTON_SCROLL_STOP, m_btn_scroll);
}


BEGIN_MESSAGE_MAP(CUartLogDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CUartLogDlg::OnBnClickedBtnSearch)
	ON_BN_CLICKED(IDC_BTN_STOPSTART, &CUartLogDlg::OnBnClickedBtnStopstart)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SCH_PRE, &CUartLogDlg::OnBnClickedButtonSchPre)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CUartLogDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_SCROLL_STOP, &CUartLogDlg::OnBnClickedButtonScrollStop)
	ON_BN_CLICKED(IDC_BTN_CLEAN, &CUartLogDlg::OnBnClickedBtnClean)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CUartLogDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IUartLogDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {80B0A025-AB7D-439B-B8B3-7E15A4D431F5}
static const IID IID_IUartLogDlg =
{ 0x80B0A025, 0xAB7D, 0x439B, { 0xB8, 0xB3, 0x7E, 0x15, 0xA4, 0xD4, 0x31, 0xF5 } };

BEGIN_INTERFACE_MAP(CUartLogDlg, CDialogEx)
	INTERFACE_PART(CUartLogDlg, IID_IUartLogDlg, Dispatch)
END_INTERFACE_MAP()


// CUartLogDlg 消息处理程序


int CUartLogDlg::AddLog(CString str)
{
	if (m_stop_refresh)
		return 0;
#if 1
	if (str == "\r")
	{
	}
	else if (str == "\n")
	{
		m_str_newLine.Append(L"\r\n");
		m_richEdit.Append(m_str_newLine, false);
		m_str_newLine.Empty();
	}
	else
	{
		m_str_newLine.Append(str);
	}
#else
	m_richEdit.Append(str, false);
#endif
	return 0;
}

BOOL CUartLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_richEdit.Initlize();


	GetClientRect(&m_rect); 


	

	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE |
		CFM_ITALIC | CFM_SIZE | CFM_UNDERLINE;
	cf.dwEffects = 0;
	cf.yHeight = 15 * 15;//文字高度 
	cf.crTextColor = RGB(255, 255, 255); //文字颜色 
	StrCpyW(cf.szFaceName, _T("微软雅黑"));//设置字体 
//	m_richEdit.SetSel(1, 5); //设置处理区域 
//	m_richEdit.SetSelectionCharFormat(cf);
	m_richEdit.SetDefaultCharFormat(cf);
	m_richEdit.SetBackgroundColor(FALSE, RGB(0, 0, 0));   //设背景色可以 



	CMySerialDlg *pMainDlg = (CMySerialDlg *)(this->GetParent());
	m_serialComDlg = (CSerialPortDlg *)(pMainDlg->m_serialComDlg);
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CUartLogDlg::OnBnClickedBtnSearch()
{
	FINDTEXTEX ft; //查找结构 
	CString find;
	m_edit_search.GetWindowText(find);

	m_pos_find = 0;
	ft.chrg.cpMin = m_pos_find;
	ft.chrg.cpMax = -1;
	ft.lpstrText = find; 

	int length = find.GetLength();

	int nCount = 0;
	do
	{
		m_pos_find = m_richEdit.FindText(FR_DOWN, &ft);
		if (-1 == m_pos_find) break;
		ft.chrg.cpMin = m_pos_find + length;
		++nCount;
	} while (FALSE);

	if (-1 != m_pos_find)
	{
		m_richEdit.SetSel(m_pos_find, m_pos_find + length);
		m_richEdit.SetFocus();
	}

	m_pos_find += length;
}
void CUartLogDlg::OnBnClickedButtonSchPre()
{
	FINDTEXTEX ft; //查找结构 
	CString find;
	m_edit_search.GetWindowText(find);
	int length = find.GetLength();


	m_pos_find -= length;
	ft.chrg.cpMin = 0;
	ft.chrg.cpMax = m_pos_find;
	ft.lpstrText = find;


	int nCount = 0;
	do
	{
		nCount = m_richEdit.FindText(FR_DOWN, &ft);
		if (-1 == nCount) break;
		ft.chrg.cpMin = nCount + length;
		m_pos_find = nCount;
	} while (TRUE);

	if (-1 != m_pos_find)
	{
		m_richEdit.SetSel(m_pos_find, m_pos_find + length);
		m_richEdit.SetFocus();
	}

	m_pos_find += length;
}


void CUartLogDlg::OnBnClickedButtonNext()
{
	FINDTEXTEX ft; //查找结构 
	CString find;
	m_edit_search.GetWindowText(find);

	if (m_pos_find == -1)
		m_pos_find = 0;
	ft.chrg.cpMin = m_pos_find;
	ft.chrg.cpMax = -1;
	ft.lpstrText = find;

	int length = find.GetLength();

	int nCount = 0;
	do
	{
		m_pos_find = m_richEdit.FindText(FR_DOWN, &ft);
		if (-1 == m_pos_find) break;
		ft.chrg.cpMin = m_pos_find + length;
		++nCount;
	} while (FALSE);

	if (-1 != m_pos_find)
	{
		m_richEdit.SetSel(m_pos_find, m_pos_find + length);
		m_richEdit.SetFocus();
		SendMessage(WM_VSCROLL, MAKEWPARAM(SB_THUMBPOSITION, m_pos_find), 0);
	}

	m_pos_find += length;
}


void CUartLogDlg::OnBnClickedBtnStopstart()
{
	CString tmp;
	m_btn_stopstart.GetWindowTextW(tmp);
	if (tmp.Find(L"暂停")>=0)
	{
		m_btn_stopstart.SetWindowTextW(L"开始");
		m_stop_refresh = 1;
	}
	else
	{
		m_btn_stopstart.SetWindowTextW(L"暂停");
		m_stop_refresh = 0;
	}
}


void CUartLogDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	if (nType == SIZE_MINIMIZED) return;
	
	ChangeSize(IDC_RICHEDIT21,cx,cy);

	GetClientRect(&m_rect);
}

void CUartLogDlg::ChangeSize(UINT nID, int x, int y)  //nID为控件ID，x,y分别为对话框的当前长和宽
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
	}
}


void CUartLogDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();

	if (GetDlgItem(IDC_EDIT_SEARCH) == GetFocus())//IDC_ED_MC是希望处理回车事件的EditCtrl控件的ID
	{
		OnBnClickedBtnSearch();
		return;//执行之后直接返回
	}
}




void CUartLogDlg::OnBnClickedButtonScrollStop()
{
	

	CString tmp;
	m_btn_scroll.GetWindowTextW(tmp);
	if (tmp.Find(L"停止滚动") >= 0)
	{
		m_btn_scroll.SetWindowTextW(L"滚动");
		m_richEdit.StopScroll();
	}
	else
	{
		m_btn_scroll.SetWindowTextW(L"停止滚动");
		m_richEdit.SetScrollBottom();
	}
}


void CUartLogDlg::OnBnClickedBtnClean()
{
	m_richEdit.SetWindowTextW(L"");
}
