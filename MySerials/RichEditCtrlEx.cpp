#include "stdafx.h"
#include <afxinet.h>
#include "RichEditCtrlEx.h"

#pragma warning(disable:4996)

CRichEditCtrlEx::CRichEditCtrlEx(void)
{
	m_ShowBorder = TRUE;
	m_BorderColor = RGB(53, 104, 187);
	m_bBottom = false;
	m_bCreate = false;
	m_bFocus = true;
	AfxInitRichEdit2();
}

CRichEditCtrlEx::~CRichEditCtrlEx(void)
{
}

IMPLEMENT_DYNCREATE(CRichEditCtrlEx, CRichEditCtrl)
BEGIN_MESSAGE_MAP(CRichEditCtrlEx, CRichEditCtrl)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
	ON_NOTIFY_REFLECT_EX(EN_LINK, OnLink)
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CRichEditCtrlEx::Initlize()
{
	m_bBottom = true;
	m_bCreate = true;
	//SetEventMask(GetEventMask() | ENM_LINK) ; 
	//SendMessage(EM_AUTOURLDETECT, TRUE, 0);
	SetOptions(ECOOP_OR, ECO_AUTOVSCROLL);  // �Զ���ֱ����
	//SetOptions(ECOOP_OR, ECO_SAVESEL);
	LimitText(0xFFFFFFFF);
	SetBackgroundColor(FALSE, RGB(248, 248, 248));
	SetLeftOffset(150);
}
void CRichEditCtrlEx::Append(LPCTSTR text, bool newline, bool link, int nLinkBegin, int nLinkCount)
{
	int nPrvTotal = GetTextLengthEx(GTL_DEFAULT, 1200);
	CHARRANGE oldsel;
	this->GetSel(oldsel);
	SetSel(-1, -1);
	ReplaceSel((LPCTSTR)text);
	if (newline)
	{
		SetSel(-1, -1);
		ReplaceSel(L"\r\n");
	}
	if (link)
	{
		if (!newline)
		{
			Append(L"\r\n");
		}
		int nTotal = GetTextLengthEx(GTL_DEFAULT, 1200) - 1;
		if (nTotal > 0)
		{
			if (nLinkCount > nTotal - nPrvTotal)
			{
				nLinkCount = nTotal - nPrvTotal;
			}
			SetSel(nPrvTotal + nLinkBegin, nPrvTotal + nLinkBegin + nLinkCount);
			AddLink();
		}
	}
	// �������������Զ����������������һ��
	if (m_bBottom)
	{
		PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
	else
		SetSel(oldsel);
}
void CRichEditCtrlEx::GetText(int nBegin, int nEnd, CString& text)
{
	CHARRANGE CharRange;
	CharRange.cpMin = nBegin;
	CharRange.cpMax = nEnd;
	SetSel(CharRange);
	CHAR szTmp[1024] = { 0 };
	GetSelText(szTmp);
	text.Format(L"%s", szTmp);
}
void CRichEditCtrlEx::SetScrollBottom(bool bottom)
{
	m_bBottom = bottom;
	if (m_bBottom)
	{
		PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	}
}
void CRichEditCtrlEx::StopScroll()
{
	m_bBottom = false;
}
void CRichEditCtrlEx::SetTextFont(int nBegin, int nEnd, bool bold, bool italic, bool underline, COLORREF color, int size)
{
	SetSel(nBegin, nEnd);
	CHARFORMAT2 cf, oldCf;
	GetSelectionCharFormat(oldCf);
	GetSelectionCharFormat(cf);
	if (bold)
	{
		cf.dwMask |= CFM_BOLD;
		cf.dwEffects |= CFE_BOLD;			//���ô��壬ȡ����cf.dwEffects&=~CFE_BOLD;
	}
	if (italic)
	{
		cf.dwMask |= CFM_ITALIC;
		cf.dwEffects |= CFE_ITALIC;		//����б�壬ȡ����cf.dwEffects&=~CFE_ITALIC;
	}
	if (underline)
	{
		cf.dwMask |= CFM_UNDERLINE;
		cf.dwEffects |= CFE_UNDERLINE;	//�����»��ߣ�ȡ����cf.dwEffects&=~CFE_UNDERLINE;
	}
	if (color)
	{
		cf.dwEffects &= ~CFE_AUTOCOLOR;	//�������Ҫ����ѡ��������ɫ��ʱ��ҲҪע��,dwEffectsһ��������CEF_AUTOCOLOR������
		cf.dwMask |= CFM_COLOR;
		cf.crTextColor = color;	//������ɫ
	}
	if (size)
	{
		cf.dwMask |= CFM_SIZE;
		cf.yHeight = 200;				//���ø߶�
	}
	cf.dwMask |= CFM_FACE;
	wcscpy_s(cf.szFaceName, L"΢���ź�");//��������
	SetSelectionCharFormat(cf);
	SetSel(-1, -1);
	SetSelectionCharFormat(oldCf);
}


void CRichEditCtrlEx::SetFontColor(COLORREF color)
{
	CHARFORMAT2 cf;
	GetSelectionCharFormat(cf);

	if (color)
	{
		cf.dwEffects &= ~CFE_AUTOCOLOR;	//�������Ҫ����ѡ��������ɫ��ʱ��ҲҪע��,dwEffectsһ��������CEF_AUTOCOLOR������
		cf.dwMask |= CFM_COLOR;
		cf.crTextColor = color;	//������ɫ
	}
	cf.dwMask |= CFM_FACE;
	cf.dwMask |= CFM_SIZE;
	cf.yHeight = 180;				//���ø߶�
	wcscpy_s(cf.szFaceName, L"΢���ź�");//��������
	SetWordCharFormat(cf);
}
void CRichEditCtrlEx::AddLink()
{
	CHARFORMAT2 cf2;
	ZeroMemory(&cf2, sizeof(CHARFORMAT2));
	cf2.cbSize = sizeof(CHARFORMAT2);

	cf2.dwMask |= CFM_LINK;
	cf2.dwEffects |= CFE_LINK;

	cf2.dwEffects &= ~CFE_AUTOCOLOR;	//�������Ҫ����ѡ��������ɫ��ʱ��ҲҪע��,dwEffectsһ��������CEF_AUTOCOLOR������
	cf2.dwMask |= CFM_COLOR;
	cf2.crTextColor = RGB(255, 112, 5);

	SetSelectionCharFormat(cf2);
	SetSel(-1, -1);
}

void CRichEditCtrlEx::CancelLink()
{
	CHARFORMAT2 cf2;
	ZeroMemory(&cf2, sizeof(CHARFORMAT2));
	cf2.cbSize = sizeof(CHARFORMAT2);
	cf2.dwMask = CFM_LINK;
	cf2.dwEffects &= ~CFE_LINK;

	SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf2);
	SetSel(-1, -1);
}
BOOL CRichEditCtrlEx::CheckURL(const CString &szUrl, CString &szMsg)
{
	DWORD dwService = 0;
	DWORD dwValid = AFX_INET_SERVICE_FTP | AFX_INET_SERVICE_HTTP | AFX_INET_SERVICE_HTTPS | AFX_INET_SERVICE_FILE;
	CString strServer;
	CString strObject;
	INTERNET_PORT port;

	BOOL bValid = AfxParseURL(szUrl, dwService, strServer, strObject, port);
	if (!bValid)
	{
		szMsg = szUrl + L" \n����һ���Ϸ������ص�ַURL";
		return FALSE;
	}
	return TRUE;
}
BOOL CRichEditCtrlEx::OnLink(NMHDR *pNotifyHeader, LRESULT *pResult)
{
	ENLINK *pEnLink = reinterpret_cast<ENLINK *>(pNotifyHeader);
	CString	  strURL;
	*pResult = 0;
	CHAR szTmpLink[512] = { 0 };
	switch (pNotifyHeader->code)
	{
	case EN_LINK:
		switch (pEnLink->msg)
		{
		case WM_LBUTTONUP:
			SetSel(pEnLink->chrg);
			GetSelText(szTmpLink);
			strURL.Format(L"%s", szTmpLink);
			CString strMsg;
			if (CheckURL(strURL, strMsg))
			{
				ShellExecute(GetSafeHwnd(), _T("open"), strURL, NULL, NULL, SW_SHOWNORMAL);
			}
			break;
		}
		break;
	}
	return *pResult;
}

//	We need to handle the OnSize message to ensure that the most recent
//	line of text is visible.
void CRichEditCtrlEx::OnSize(UINT nType, int cx, int cy)
{
	CRichEditCtrl::OnSize(nType, cx, cy);
}
void CRichEditCtrlEx::OnSize(CWnd* pParent)
{
	if (!m_bCreate)
	{
		return;
	}
	CRect parentRect;
	pParent->GetClientRect(parentRect);
	parentRect.bottom = parentRect.bottom - 5;
	parentRect.top = parentRect.top + 5;
	parentRect.left = parentRect.left + 5;
	parentRect.right = parentRect.right - 5;
	MoveWindow(parentRect, TRUE);
}
void CRichEditCtrlEx::OnSize(CRect& rect)
{
	if (!m_bCreate)
	{
		return;
	}
	rect.bottom = rect.bottom - 5;
	rect.top = rect.top + 5;
	rect.left = rect.left + 5;
	rect.right = rect.right - 5;
	MoveWindow(rect, TRUE);
}
void CRichEditCtrlEx::OnSpecifySize(CWnd* pParent)
{
	if (!m_bCreate)
	{
		return;
	}
	CRect parentRect;
	pParent->GetClientRect(parentRect);
	parentRect.left = 5;
	parentRect.top = 197;
	parentRect.right -= 5;
	parentRect.bottom -= 5;
	MoveWindow(parentRect, TRUE);

}
void CRichEditCtrlEx::OnPaint()
{
	if (!m_ShowBorder)
	{
		CRichEditCtrl::OnPaint();
		return;
	}
	CRichEditCtrl::OnPaint();
	CClientDC dc(this);
	if (!m_pParentWnd)
	{
		return;
	}
	CRect rect;
	GetWindowRect(rect);
	rect.left -= 1;
	rect.top -= 1;
	rect.right += 1;
	rect.bottom += 1;
	ScreenToClient(rect);
	dc.Draw3dRect(rect, m_BorderColor, m_BorderColor);
}
// ����ؼ����Ի�ý��㣬�򵱿ؼ��н���ʱ���Զ��������ײ�������Ҫ����һ��
void CRichEditCtrlEx::OnSetFocus(CWnd* pOldWnd)
{
	if (!m_bFocus)
	{
		return;
	}
	CRichEditCtrl::OnSetFocus(pOldWnd);
}

bool CRichEditCtrlEx::IsCreate()
{
	return m_bCreate;
}
void CRichEditCtrlEx::Clear()
{
	if (GetWindowLong(this->m_hWnd, GWL_STYLE) & ES_READONLY)
	{
		SetReadOnly(FALSE);
		CRichEditCtrl::Clear();
		SetReadOnly();
	}
	else
	{
		CRichEditCtrl::Clear();
	}
}
void CRichEditCtrlEx::SetEditFocus(bool focus)
{
	m_bFocus = focus;
}
void CRichEditCtrlEx::ShowBorderLine(BOOL bShow, COLORREF nColor)
{
	m_ShowBorder = bShow;
}
void CRichEditCtrlEx::SetLeftOffset(int nOffset)
{
	PARAFORMAT2 PF_his;
	PF_his.dwMask = PFM_ALIGNMENT | PFM_STARTINDENT;
	PF_his.wAlignment = PFA_LEFT;
	PF_his.dxStartIndent = nOffset;
	SetParaFormat(PF_his);
}
#pragma warning(default:4996)


void CRichEditCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	//	StopScroll();

	CRichEditCtrl::OnLButtonDown(nFlags, point);
}
