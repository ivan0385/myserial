#pragma once
#include "afxcmn.h"



/////////////////////////////////////////////////////////////////////////////
// Name:        RICHEDITCTRLEX.H
// Purpose:     CRichEditCtrlEx
// Author:      yfq
// Modified by: 
// Created:     2010/12/24 11:01
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

class CRichEditCtrlEx :	public CRichEditCtrl
{
	DECLARE_DYNCREATE(CRichEditCtrlEx)
public:
	CRichEditCtrlEx(void);
	~CRichEditCtrlEx(void);
	
	void Initlize();
	/**
	* ���׷��һ��
	*
	* @param text -[in] -Ҫ׷�ӵ��ı�
	*
	* @param newline -[in] -�Ƿ���
	*
	* @param link	 -[in] -�Ƿ��������
	*
	* @param nLinkBegin -[in] -��������ʼλ��(������0��ʼ)
	*
	* @param nLinkCount -[in] -�������ַ���
	*
	* @return -[NONE]
	*/
	void Append(LPCTSTR text,bool newline = false,bool link = false,int nLinkBegin = 0,int nLinkCount = 0);
	
	/**
	 * ����ı�
	 *
	 * @param nBegin -[in] -��ʼλ��
	 *
	 * @param nEnd -[in] -����λ��
	 *
	 * @param text -[out] -�õ����ı�
	 *
	 * @return -[NONE]
	 */
	void GetText(int nBegin,int nEnd,CString& text);
	
	/**
	 * ��������ʱ�Ƿ�������ײ�
	 *
	 * @param bottom -[in] -��������ײ�
	 *
	 * @return -[NONE]
	 */
	void SetScrollBottom(bool bottom=true);
	void StopScroll();

	/**
	 * ��������
	 *
	 * @param nBegin -[in] -��ʼλ��
	 *
	 * @param nEnd -[in] -����λ��
	 *
	 * @param bold -[in] -����
	 *
	 * @param italic -[in] -б��
	 *
	 * @param underline -[in] -�»���
	 *
	 * @param color -[in] -��ɫ
	 *
	 * @param size -[in] -���ִ�С
	 *
	 * @return -[NONE]
	 */
	void SetTextFont(int nBegin,int nEnd,bool bold,bool italic,bool underline,COLORREF color=0,int size=0);
	
	/**
	 * Ϊѡ�е��ı���ӳ�����
	 *
	 * @return -[NONE]
	 */
	void AddLink();

	/**
	 * ȡ��ѡ���ı���ĳ�����
	 *
	 * @return -[NONE]
	 */
	void CancelLink();

	/**
	* У��URL�Ƿ�Ϸ��ļ�·��������Ϊrfc2396
	* �������ֻ�����Ե�У�飬����ȫ����RFC2369
	* ��֧��IPV4
	*
	*/
	BOOL CheckURL(const CString &szUrl, CString &szMsg);

	void OnSize(CWnd* pParent);
	void OnSize(CRect& rect);
	void OnSpecifySize(CWnd* pParent);
	bool IsCreate();
	void Clear();
	void SetEditFocus(bool focus);
	
	/**
	 * ��ʾָ����ɫ�ı߿�
	 *
	 * @param bShow -[in] -�Ƿ���ʾ�߿�
	 *
	 * @param nColor -[in] -�߿���ɫ
	 *
	 * @return -[NONE]
	 */
	void ShowBorderLine(BOOL bShow,COLORREF nColor = RGB(53, 104, 187));
	
	/**
	 * �������ƫ��
	 *
	 * @param nOffset -[in] -ƫ����
	 *
	 * @return -[NONE]
	 */
	void SetLeftOffset(int nOffset);
	void SetFontColor(COLORREF color);
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnLink(NMHDR *in_pNotifyHeader, LRESULT *out_pResult);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	DECLARE_MESSAGE_MAP()

private:
	CWnd*		m_pParentWnd;
	bool		m_bBottom;
	BOOL		m_ShowBorder; 
	COLORREF	m_BorderColor; 
	bool		m_bCreate;
	bool		m_bFocus;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

