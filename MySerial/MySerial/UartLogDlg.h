#pragma once
#include "afxwin.h"

#include "SerialPortDlg.h"
#include "richeditctrlex.h"
#include "atltypes.h"

// CUartLogDlg �Ի���

class CUartLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUartLogDlg)

public:
	CUartLogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUartLogDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	int AddLog(CString str);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedBtnA1();
	afx_msg void OnBnClickedBtnA2();
	CButton m_btn_a1;
	CButton m_btn_a2;
	CEdit m_edit1;
	CEdit m_edit2;
	virtual BOOL OnInitDialog();
	CSerialPortDlg *m_serialComDlg;
	CRichEditCtrlEx m_richEdit;
	CButton m_btn_stopstart;
	CEdit m_edit_search;
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnBnClickedBtnStopstart();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CRect m_richedit_rect;
	void ChangeSize(UINT nID, int x, int y);
	CRect m_rect;
	int m_stop_refresh;
	virtual void OnOK();
	afx_msg void OnBnClickedButtonSchPre();
	afx_msg void OnBnClickedButtonNext();
	CButton m_btn_scroll;
	afx_msg void OnBnClickedButtonScrollStop();
	CString m_str_newLine;
	afx_msg void OnBnClickedBtnClean();
	unsigned long m_pos_find;
};
