// UartLogDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "MySerial.h"
#include "UartLogDlg.h"
#include "afxdialogex.h"


#include "MySerialDlg.h"

// CUartLogDlg �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IUartLogDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {80B0A025-AB7D-439B-B8B3-7E15A4D431F5}
static const IID IID_IUartLogDlg =
{ 0x80B0A025, 0xAB7D, 0x439B, { 0xB8, 0xB3, 0x7E, 0x15, 0xA4, 0xD4, 0x31, 0xF5 } };

BEGIN_INTERFACE_MAP(CUartLogDlg, CDialogEx)
	INTERFACE_PART(CUartLogDlg, IID_IUartLogDlg, Dispatch)
END_INTERFACE_MAP()


// CUartLogDlg ��Ϣ�������


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
	cf.yHeight = 15 * 15;//���ָ߶� 
	cf.crTextColor = RGB(255, 255, 255); //������ɫ 
	StrCpyW(cf.szFaceName, _T("΢���ź�"));//�������� 
//	m_richEdit.SetSel(1, 5); //���ô������� 
//	m_richEdit.SetSelectionCharFormat(cf);
	m_richEdit.SetDefaultCharFormat(cf);
	m_richEdit.SetBackgroundColor(FALSE, RGB(0, 0, 0));   //�豳��ɫ���� 



	CMySerialDlg *pMainDlg = (CMySerialDlg *)(this->GetParent());
	m_serialComDlg = (CSerialPortDlg *)(pMainDlg->m_serialComDlg);
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CUartLogDlg::OnBnClickedBtnSearch()
{
	FINDTEXTEX ft; //���ҽṹ 
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
	FINDTEXTEX ft; //���ҽṹ 
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
	FINDTEXTEX ft; //���ҽṹ 
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
	if (tmp.Find(L"��ͣ")>=0)
	{
		m_btn_stopstart.SetWindowTextW(L"��ʼ");
		m_stop_refresh = 1;
	}
	else
	{
		m_btn_stopstart.SetWindowTextW(L"��ͣ");
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

void CUartLogDlg::ChangeSize(UINT nID, int x, int y)  //nIDΪ�ؼ�ID��x,y�ֱ�Ϊ�Ի���ĵ�ǰ���Ϳ�
{
	CWnd *pWnd;
	pWnd = GetDlgItem(nID);
	if (pWnd != NULL)     //�ж��Ƿ�Ϊ�գ���Ϊ�ڴ��ڴ�����ʱ��Ҳ�����OnSize���������Ǵ�ʱ�����ؼ���û�д�����PwndΪ��
	{
		CRect rec;
		pWnd->GetWindowRect(&rec);  //��ȡ�ؼ��仯ǰ�Ĵ�С
		ScreenToClient(&rec);   //���ؼ���Сװ��λ�ڶԻ����е���������
		//rec.left = rec.left*x / m_rect.Width();  //���ձ��������ռ����λ��
		//rec.top = rec.top*y / m_rect.Height();
		rec.bottom = rec.bottom*y / m_rect.Height();
		rec.right = rec.right*x / m_rect.Width();
		pWnd->MoveWindow(rec);   //�����ؼ�
	}
}


void CUartLogDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	//CDialogEx::OnOK();

	if (GetDlgItem(IDC_EDIT_SEARCH) == GetFocus())//IDC_ED_MC��ϣ������س��¼���EditCtrl�ؼ���ID
	{
		OnBnClickedBtnSearch();
		return;//ִ��֮��ֱ�ӷ���
	}
}




void CUartLogDlg::OnBnClickedButtonScrollStop()
{
	

	CString tmp;
	m_btn_scroll.GetWindowTextW(tmp);
	if (tmp.Find(L"ֹͣ����") >= 0)
	{
		m_btn_scroll.SetWindowTextW(L"����");
		m_richEdit.StopScroll();
	}
	else
	{
		m_btn_scroll.SetWindowTextW(L"ֹͣ����");
		m_richEdit.SetScrollBottom();
	}
}


void CUartLogDlg::OnBnClickedBtnClean()
{
	m_richEdit.SetWindowTextW(L"");
}
