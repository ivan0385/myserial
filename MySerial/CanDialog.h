#pragma once

//can communication
#include "CanDevice.h"
#include "CanMatrix.h"
#include "afxwin.h"
#include "afxcmn.h"
// CCanDialog 对话框




//////////////////////////////////////////////////////////////////////////
class c_dlg_data_receiver : public i_data_receiver
{
public:
	c_dlg_data_receiver(CDialog* ptr=NULL)
	{
		ptr_canDlg = ptr;
	}

	// interface i_data_receiver
	virtual void receive(const VCI_CAN_OBJ * ba, int cb);
	virtual void reset_buffer() {}
	inline void setDlg(CDialog* ptr)
	{
		ptr_canDlg = ptr;
	}
protected:
	CDialog  *ptr_canDlg;
};





class CCanDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CCanDialog)

public:
	CCanDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCanDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_CAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioIgn();
	CanDevice *m_canDevice;
	CanMatrix *m_canData;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckBcm1Enable();
	afx_msg void OnBnClickedRadioLAMP();
	afx_msg void OnBnClickedRadioReverse();
	afx_msg void OnBnClickedCheckIc1Enable();
	CEdit m_edit_speed;
	afx_msg void OnEnChangeEditSpeed();
	CSliderCtrl m_slider_speed;
	afx_msg void OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboPdc1Number();
	afx_msg void OnCbnSelchangeComboPdc1Min();
	afx_msg void OnCbnSelchangeComboPdc1DistFl();
	afx_msg void OnCbnSelchangeComboPdc1DistFml();
	afx_msg void OnCbnSelchangeComboPdc1DistFmr();
	afx_msg void OnCbnSelchangeComboPdc1DistFr();
	afx_msg void OnCbnSelchangeComboPdc1DistRl();
	afx_msg void OnCbnSelchangeComboPdc1DistRml();
	afx_msg void OnCbnSelchangeComboPdc1DistRmr();
	afx_msg void OnCbnSelchangeComboPdc1DistRr();
	afx_msg void OnBnClickedCheck1Pdc1SensrFl();
	afx_msg void OnBnClickedCheck1Pdc1SensrFml();
	afx_msg void OnBnClickedCheck1Pdc1SensrFmr();
	afx_msg void OnBnClickedCheck1Pdc1SensrFr();
	afx_msg void OnBnClickedCheckPdc1SensrSys();
	afx_msg void OnBnClickedCheck1Pdc1SensrRl();
	afx_msg void OnBnClickedCheck1Pdc1SensrRml();
	afx_msg void OnBnClickedCheck1Pdc1SensrRmr();
	afx_msg void OnBnClickedCheck1Pdc1SensrRr();
	afx_msg void OnBnClickedCheckIce4SideviewEnable();
	afx_msg void OnBnClickedCheckIce4PdcviewEnable();
	afx_msg void OnCbnSelchangeComboIce4Carcolor();
	afx_msg void OnBnClickedButtonIce4Avm();
	afx_msg void OnBnClickedButtonIce4Calib();
	afx_msg void OnBnClickedRadioIce5();
	afx_msg void OnBnClickedButtonOpencan();
	afx_msg void OnBnClickedButtonClosecan();
	CEdit m_edit_rcv_sideview;
	CEdit m_edit_pdcview;
	CEdit m_edit_rcv_videoOnOff;
	CEdit m_edit_angle;
	CSliderCtrl m_slider_angle;
	afx_msg void OnEnChangeEditAngle();
	afx_msg void OnNMCustomdrawSliderAngle(NMHDR *pNMHDR, LRESULT *pResult);

	c_dlg_data_receiver m_receiver;
	afx_msg void OnBnClickedButtonComPort();
	CButton m_btn_send;
	CButton m_edit_send_stop;
	CEdit m_edit_snd_data;
	CEdit m_edit_send_id;
	CEdit m_edit_cycle;
	afx_msg void OnBnClickedButtonSnd();
	afx_msg void OnBnClickedButtonStopsnd();
	afx_msg void OnBnClickedButtonComPort2();
	afx_msg void OnBnClickedButtonScrn();
	CEdit m_edit_touch_x;
	CEdit m_edit_touch_y;
	CSliderCtrl m_slider_x;
	CSliderCtrl m_slider_y;
	afx_msg void OnNMCustomdrawSliderX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderY(NMHDR *pNMHDR, LRESULT *pResult);
};

