#pragma once

#include "CommThread.h"

// CSerialPortDlg 对话框

class CSerialPortDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSerialPortDlg)

public:
	CSerialPortDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSerialPortDlg();

	virtual void OnFinalRelease();

	// 对话框数据
	enum { IDD = IDD_COM_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CComboBox m_com_port;
	CComboBox m_com_rate;
	CComboBox m_com_dataBit;
	CComboBox m_com_stopBit;
	CComboBox m_com_parity;
	virtual BOOL OnInitDialog();
	int m_iComPort;
	int m_iComBaudRate;
	int m_iDataBit;
	int m_iStopBit;
	int m_iParity;
	CButton m_btn_com_open;
	CButton m_btn_com_close;
	afx_msg void OnBnClickedBtnOpenPort();
	CString byIndexComPort(int xPort);
	DWORD byIndexBaud(int xBaud);
	BYTE byIndexData(int xData);
	BYTE byIndexStop(int xStop);
	BYTE byIndexParity(int xParity);
	afx_msg void OnBnClickedBtnClosePort();

	CCommThread m_CommThread;
	int SendAsciiData(CString inputStr);
protected:
	afx_msg LRESULT OnCommRead(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButton1();
	int SendHexData(CString inputStr);
	int ConvertHexChar(char ch);
	BOOL m_bIsComConnect;
	CString m_tempRcvCmd;
	int m_tempRcvCmdCount;
	int m_tempRcvCmdSize;
	BOOL m_bBtFanetConnected;
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);
	void FindFunc(void);
	CString m_strCurFunc;
	afx_msg void OnClose();

	static void com_udpate_list_callback(void* ud, const t_com_item* t);

};
