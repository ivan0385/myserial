
// MySerialDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include "UartLogDlg.h"
#include "SerialPortDlg.h"
#include "afxcmn.h"
#include "atltypes.h"

#include "CanDialog.h"

#include "CanDevice.h"
#include "CanMatrix.h"

// CMySerialDlg 对话框
class CMySerialDlg : public CDialogEx
{
// 构造
public:
	CMySerialDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYSERIAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnConnectionNewconnection();
	CEdit m_edit_s1;
	CEdit m_edit_s2;
	CEdit m_edit_s3;
	CEdit m_edit_s4;
	CEdit m_edit_s5;
	CEdit m_edit_s6;
	CEdit m_edit_s7;
	CEdit m_edit_s8;
	CEdit m_edit_s9;
	
	CSerialPortDlg *m_serialComDlg;
	CCanDialog *m_canDlg;
	CUartLogDlg *m_uartLogDlg;
	afx_msg void OnDestroy();
	CTabCtrl m_tab_main;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ChangeSize(UINT nID, int x, int y);
	CRect m_rect;
	int m_isinit;
	afx_msg void OnBnClickedBtnNfs();
	afx_msg void OnBnClickedBtnCpsvp();
	afx_msg void OnBnClickedBtnCpbin();
	afx_msg void OnBnClickedBtnCpradio();
	afx_msg void OnBnClickedReboot();
	afx_msg void OnBnClickedBtnRvs1();
	afx_msg void OnBnClickedBtnRvs0();
	afx_msg void OnBnClickedBtnTurnleft1();
	afx_msg void OnBnClickedBtnTurnleft0();
	afx_msg void OnBnClickedBtnTurnrght1();
	afx_msg void OnBnClickedBtnTurnrght0();
	afx_msg void OnDeltaposSpinSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnS1();
	afx_msg void OnBnClickedBtnS2();
	afx_msg void OnBnClickedBtnS3();
	afx_msg void OnBnClickedBtnS4();
	afx_msg void OnBnClickedBtnS5();
	afx_msg void OnBnClickedBtnS6();
	afx_msg void OnBnClickedBtnS7();
	afx_msg void OnBnClickedBtnS8();
	afx_msg void OnBnClickedBtnS9();
	afx_msg void OnBnClickedBtnRadar();
	afx_msg void OnBnClickedBtnSetting();
	afx_msg void OnBnClickedBtnEol();
	int m_speed;
	int m_angle;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_edit_speed;
	CEdit m_edit_angle;
	virtual void OnOK();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonIgn();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3d();
	afx_msg void OnBnClickedButton3();
	CanDevice * m_canDevice;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CanMatrix * m_canData;
	afx_msg void OnConnection32772();
	afx_msg void OnBnClickedBtnCpsvp2();
	CEdit m_edit_s10;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
