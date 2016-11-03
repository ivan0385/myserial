// CanDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MySerial.h"
#include "CanDialog.h"
#include "afxdialogex.h"

#include "MyString.h"



// CCanDialog 对话框

IMPLEMENT_DYNAMIC(CCanDialog, CDialogEx)

CCanDialog::CCanDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCanDialog::IDD, pParent)
	, m_canDevice(NULL)
	, m_canData(NULL)
{

}

CCanDialog::~CCanDialog()
{
}

void CCanDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SPEED, m_edit_speed);
	DDX_Control(pDX, IDC_SLIDER_SPEED, m_slider_speed);
	DDX_Control(pDX, IDC_EDIT_RCV_SIDEVIEW, m_edit_rcv_sideview);
	DDX_Control(pDX, IDC_EDIT_RCV_PDCVIEW, m_edit_pdcview);
	DDX_Control(pDX, IDC_EDIT_RCV_VIDEO_ONOFF, m_edit_rcv_videoOnOff);
	DDX_Control(pDX, IDC_EDIT_ANGLE, m_edit_angle);
	DDX_Control(pDX, IDC_SLIDER_ANGLE, m_slider_angle);
	DDX_Control(pDX, IDC_BUTTON_SND, m_btn_send);
	DDX_Control(pDX, IDC_BUTTON_STOPSND, m_edit_send_stop);
	DDX_Control(pDX, IDC_EDIT_SND_DATA, m_edit_snd_data);
	DDX_Control(pDX, IDC_EDIT_SND_ID, m_edit_send_id);
	DDX_Control(pDX, IDC_EDIT_SND_cycle, m_edit_cycle);
	DDX_Control(pDX, IDC_EDIT_TOUCH_X, m_edit_touch_x);
	DDX_Control(pDX, IDC_EDIT_TOUCH_Y, m_edit_touch_y);
	DDX_Control(pDX, IDC_SLIDER_X, m_slider_x);
	DDX_Control(pDX, IDC_SLIDER_Y, m_slider_y);
}


BEGIN_MESSAGE_MAP(CCanDialog, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_IGN_ON, &CCanDialog::OnBnClickedRadioIgn)
	ON_BN_CLICKED(IDC_CHECK_BCM1_ENABLE, &CCanDialog::OnBnClickedCheckBcm1Enable)
	ON_BN_CLICKED(IDC_RADIO_IGN_OFF, &CCanDialog::OnBnClickedRadioIgn)
	ON_BN_CLICKED(IDC_RADIO_IGN_ACC, &CCanDialog::OnBnClickedRadioIgn)
	ON_BN_CLICKED(IDC_RADIO_LEFT, &CCanDialog::OnBnClickedRadioLAMP)
	ON_BN_CLICKED(IDC_RADIO_RIGHT, &CCanDialog::OnBnClickedRadioLAMP)
	ON_BN_CLICKED(IDC_RADIO_BOTH, &CCanDialog::OnBnClickedRadioLAMP)
	ON_BN_CLICKED(IDC_RADIO_LAMP_OFF, &CCanDialog::OnBnClickedRadioLAMP)
	ON_BN_CLICKED(IDC_RADIO_REVERSE_ON, &CCanDialog::OnBnClickedRadioReverse)
	ON_BN_CLICKED(IDC_RADIO_REVERSE_OFF, &CCanDialog::OnBnClickedRadioReverse)
	ON_BN_CLICKED(IDC_CHECK_IC1_ENABLE, &CCanDialog::OnBnClickedCheckIc1Enable)
	ON_EN_CHANGE(IDC_EDIT_SPEED, &CCanDialog::OnEnChangeEditSpeed)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SPEED, &CCanDialog::OnNMCustomdrawSliderSpeed)
	ON_CBN_SELCHANGE(IDC_COMBO_PDC1_NUMBER, &CCanDialog::OnCbnSelchangeComboPdc1Number)
	ON_CBN_SELCHANGE(IDC_COMBO_PDC1_MIN, &CCanDialog::OnCbnSelchangeComboPdc1Min)
	ON_CBN_SELCHANGE(IDC_COMBO_PDC1_DIST_FL, &CCanDialog::OnCbnSelchangeComboPdc1DistFl)
	ON_CBN_SELCHANGE(IDC_COMBO_PDC1_DIST_FML, &CCanDialog::OnCbnSelchangeComboPdc1DistFml)
	ON_CBN_SELCHANGE(IDC_COMBO_PDC1_DIST_FMR, &CCanDialog::OnCbnSelchangeComboPdc1DistFmr)
	ON_CBN_SELCHANGE(IDC_COMBO_PDC1_DIST_FR, &CCanDialog::OnCbnSelchangeComboPdc1DistFr)
	ON_CBN_SELCHANGE(IDC_COMBO_PDC1_DIST_RL, &CCanDialog::OnCbnSelchangeComboPdc1DistRl)
	ON_CBN_SELCHANGE(IDC_COMBO_PDC1_DIST_RML, &CCanDialog::OnCbnSelchangeComboPdc1DistRml)
	ON_CBN_SELCHANGE(IDC_COMBO_PDC1_DIST_RMR, &CCanDialog::OnCbnSelchangeComboPdc1DistRmr)
	ON_CBN_SELCHANGE(IDC_COMBO_PDC1_DIST_RR, &CCanDialog::OnCbnSelchangeComboPdc1DistRr)
	ON_BN_CLICKED(IDC_CHECK1_PDC1_SENSR_FL, &CCanDialog::OnBnClickedCheck1Pdc1SensrFl)
	ON_BN_CLICKED(IDC_CHECK1_PDC1_SENSR_FML, &CCanDialog::OnBnClickedCheck1Pdc1SensrFml)
	ON_BN_CLICKED(IDC_CHECK1_PDC1_SENSR_FMR, &CCanDialog::OnBnClickedCheck1Pdc1SensrFmr)
	ON_BN_CLICKED(IDC_CHECK1_PDC1_SENSR_FR, &CCanDialog::OnBnClickedCheck1Pdc1SensrFr)
	ON_BN_CLICKED(IDC_CHECK_PDC1_SENSR_SYS, &CCanDialog::OnBnClickedCheckPdc1SensrSys)
	ON_BN_CLICKED(IDC_CHECK1_PDC1_SENSR_RL, &CCanDialog::OnBnClickedCheck1Pdc1SensrRl)
	ON_BN_CLICKED(IDC_CHECK1_PDC1_SENSR_RML, &CCanDialog::OnBnClickedCheck1Pdc1SensrRml)
	ON_BN_CLICKED(IDC_CHECK1_PDC1_SENSR_RMR, &CCanDialog::OnBnClickedCheck1Pdc1SensrRmr)
	ON_BN_CLICKED(IDC_CHECK1_PDC1_SENSR_RR, &CCanDialog::OnBnClickedCheck1Pdc1SensrRr)
	ON_BN_CLICKED(IDC_CHECK_ICE4_SIDEVIEW_ENABLE, &CCanDialog::OnBnClickedCheckIce4SideviewEnable)
	ON_BN_CLICKED(IDC_CHECK_ICE4_PDCVIEW_ENABLE, &CCanDialog::OnBnClickedCheckIce4PdcviewEnable)
	ON_CBN_SELCHANGE(IDC_COMBO_ICE4_CARCOLOR, &CCanDialog::OnCbnSelchangeComboIce4Carcolor)
	ON_BN_CLICKED(IDC_BUTTON_ICE4_AVM, &CCanDialog::OnBnClickedButtonIce4Avm)
	ON_BN_CLICKED(IDC_BUTTON_ICE4_CALIB, &CCanDialog::OnBnClickedButtonIce4Calib)
	ON_BN_CLICKED(IDC_RADIO_ICE5_800_600, &CCanDialog::OnBnClickedRadioIce5)
	ON_BN_CLICKED(IDC_RADIO_ICE5_1024_600, &CCanDialog::OnBnClickedRadioIce5)
	ON_BN_CLICKED(IDC_BUTTON_OPENCAN, &CCanDialog::OnBnClickedButtonOpencan)
	ON_BN_CLICKED(IDC_BUTTON_CLOSECAN, &CCanDialog::OnBnClickedButtonClosecan)
	ON_EN_CHANGE(IDC_EDIT_ANGLE, &CCanDialog::OnEnChangeEditAngle)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ANGLE, &CCanDialog::OnNMCustomdrawSliderAngle)
	ON_BN_CLICKED(IDC_BUTTON_COM_PORT, &CCanDialog::OnBnClickedButtonComPort)
	ON_BN_CLICKED(IDC_BUTTON_SND, &CCanDialog::OnBnClickedButtonSnd)
	ON_BN_CLICKED(IDC_BUTTON_STOPSND, &CCanDialog::OnBnClickedButtonStopsnd)
	ON_BN_CLICKED(IDC_BUTTON_COM_PORT2, &CCanDialog::OnBnClickedButtonComPort2)
	ON_BN_CLICKED(IDC_BUTTON_SCRN, &CCanDialog::OnBnClickedButtonScrn)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_X, &CCanDialog::OnNMCustomdrawSliderX)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Y, &CCanDialog::OnNMCustomdrawSliderY)
END_MESSAGE_MAP()


// CCanDialog 消息处理程序


BOOL CCanDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_canDevice = new CanDevice(2);
	m_canData = new CanMatrix;
	
	m_slider_speed.SetRange(0, 120);
	m_slider_angle.SetRange(0,0x3cef);
	m_slider_angle.SetPos(0);

	m_receiver.setDlg(this);
	m_canDevice->add_data_receiver(&m_receiver);

	m_edit_snd_data.SetWindowTextW(L"00 00 00 00 00 00 00 00");
	m_edit_send_id.SetWindowTextW(L"00 00");
	m_edit_cycle.SetWindowTextW(L"100");

	return TRUE;  // return TRUE unless you set the focus to a control
}



void CCanDialog::OnBnClickedRadioIgn()
{
	if (IsDlgButtonChecked(IDC_RADIO_IGN_ON))
	{
		m_canDevice->CanSendNormalData(m_canData->setBcm1_Ign(BCM1_IGN_START));
	}

	else if (IsDlgButtonChecked(IDC_RADIO_IGN_ACC))
	{
		m_canDevice->CanSendNormalData(m_canData->setBcm1_Ign(BCM1_IGN_ACC));
	}
	else if (IsDlgButtonChecked(IDC_RADIO_IGN_OFF))
	{
		m_canDevice->CanSendNormalData(m_canData->setBcm1_Ign(BCM1_IGN_OFF));
	}
}


void CCanDialog::OnBnClickedRadioLAMP()
{
	if (IsDlgButtonChecked(IDC_RADIO_LEFT))
	{
		m_canDevice->CanSendNormalData(m_canData->setBcm1_lamp(BCM1_LAMP_TURNLEFT));
	}

	else if (IsDlgButtonChecked(IDC_RADIO_RIGHT))
	{
		m_canDevice->CanSendNormalData(m_canData->setBcm1_lamp(BCM1_LAMP_TURNRIGHT));
	}
	else if (IsDlgButtonChecked(IDC_RADIO_BOTH))
	{
		m_canDevice->CanSendNormalData(m_canData->setBcm1_lamp(BCM1_LAMP_TURNBOTH));
	}
	else if (IsDlgButtonChecked(IDC_RADIO_LAMP_OFF))
	{
		m_canDevice->CanSendNormalData(m_canData->setBcm1_lamp(BCM1_LAMP_OFF));
	}
}

void CCanDialog::OnBnClickedCheckBcm1Enable()
{
	if (IsDlgButtonChecked(IDC_CHECK_BCM1_ENABLE))
	{
		(CButton *)this->GetDlgItem(IDC_RADIO_IGN_ON)->EnableWindow(true);
		(CButton *)this->GetDlgItem(IDC_RADIO_IGN_ACC)->EnableWindow(true);
		(CButton *)this->GetDlgItem(IDC_RADIO_IGN_OFF)->EnableWindow(true);
		(CButton *)this->GetDlgItem(IDC_RADIO_LEFT)->EnableWindow(true);
		(CButton *)this->GetDlgItem(IDC_RADIO_RIGHT)->EnableWindow(true);
		(CButton *)this->GetDlgItem(IDC_RADIO_BOTH)->EnableWindow(true);
		(CButton *)this->GetDlgItem(IDC_RADIO_LAMP_OFF)->EnableWindow(true);
	}
	else
	{
		(CButton *)this->GetDlgItem(IDC_RADIO_IGN_ON)->EnableWindow(false);
		(CButton *)this->GetDlgItem(IDC_RADIO_IGN_ACC)->EnableWindow(false);
		(CButton *)this->GetDlgItem(IDC_RADIO_IGN_OFF)->EnableWindow(false);
		(CButton *)this->GetDlgItem(IDC_RADIO_LEFT)->EnableWindow(false);
		(CButton *)this->GetDlgItem(IDC_RADIO_RIGHT)->EnableWindow(false);
		(CButton *)this->GetDlgItem(IDC_RADIO_BOTH)->EnableWindow(false);
		(CButton *)this->GetDlgItem(IDC_RADIO_LAMP_OFF)->EnableWindow(false);
	}
}

void CCanDialog::OnBnClickedRadioReverse()
{
	if (IsDlgButtonChecked(IDC_RADIO_REVERSE_ON))
	{
		m_canDevice->CanSendNormalData(m_canData->setIc1_reverse(IC1_REVERSE_GEAR));
	}
	else if (IsDlgButtonChecked(IDC_RADIO_REVERSE_OFF))
	{
		m_canDevice->CanSendNormalData(m_canData->setIc1_reverse(IC1_REVERSE_OFF));
	}
}


void CCanDialog::OnBnClickedCheckIc1Enable()
{
	if (IsDlgButtonChecked(IDC_CHECK_IC1_ENABLE))
	{
		(CButton *)this->GetDlgItem(IDC_RADIO_REVERSE_ON)->EnableWindow(true);
		(CButton *)this->GetDlgItem(IDC_RADIO_REVERSE_OFF)->EnableWindow(true);
	}
	else
	{
		(CButton *)this->GetDlgItem(IDC_RADIO_REVERSE_ON)->EnableWindow(false);
		(CButton *)this->GetDlgItem(IDC_RADIO_REVERSE_OFF)->EnableWindow(false);
	}
}


void CCanDialog::OnEnChangeEditSpeed()
{
	CString strSpd;
	int speed;
	m_edit_speed.GetWindowText(strSpd);

	speed = _ttoi(strSpd);
	m_canDevice->CanSendNormalData(m_canData->setAbs1_speed(speed));
	m_slider_speed.SetPos(speed);
}


void CCanDialog::OnNMCustomdrawSliderSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	static int i = -1;
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	CString strSpd;
	int speed = m_slider_speed.GetPos();
	if (i != speed)
	{
		strSpd.Format(L"%d", speed);
		m_edit_speed.SetWindowText(strSpd);
		i = speed;
	}
	*pResult = 0;
}


void CCanDialog::OnCbnSelchangeComboPdc1Number()
{	 
	CComboBox * cb = (CComboBox *)this->GetDlgItem(IDC_COMBO_PDC1_NUMBER);
	int index = cb->GetCurSel();
	m_canDevice->CanSendNormalData(m_canData->setPdc1_number(index));

	switch (index)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}
}


void CCanDialog::OnCbnSelchangeComboPdc1Min()
{
	CComboBox * cb = (CComboBox *)this->GetDlgItem(IDC_COMBO_PDC1_MIN);

	m_canDevice->CanSendNormalData(m_canData->setPdc1_dist_min(cb->GetCurSel()));
}


void CCanDialog::OnCbnSelchangeComboPdc1DistFl()
{
	CComboBox * cb = (CComboBox *)this->GetDlgItem(IDC_COMBO_PDC1_DIST_FL);
	m_canDevice->CanSendNormalData(m_canData->setPdc1_dist_fl(cb->GetCurSel()));
}


void CCanDialog::OnCbnSelchangeComboPdc1DistFml()
{
	CComboBox * cb = (CComboBox *)this->GetDlgItem(IDC_COMBO_PDC1_DIST_FML);
	m_canDevice->CanSendNormalData(m_canData->setPdc1_dist_fml(cb->GetCurSel()));
}


void CCanDialog::OnCbnSelchangeComboPdc1DistFmr()
{
	CComboBox * cb = (CComboBox *)this->GetDlgItem(IDC_COMBO_PDC1_DIST_FMR);
	m_canDevice->CanSendNormalData(m_canData->setPdc1_dist_fmr(cb->GetCurSel()));
}


void CCanDialog::OnCbnSelchangeComboPdc1DistFr()
{
	CComboBox * cb = (CComboBox *)this->GetDlgItem(IDC_COMBO_PDC1_DIST_FR);
	m_canDevice->CanSendNormalData(m_canData->setPdc1_dist_fr(cb->GetCurSel()));
}


void CCanDialog::OnCbnSelchangeComboPdc1DistRl()
{
	CComboBox * cb = (CComboBox *)this->GetDlgItem(IDC_COMBO_PDC1_DIST_RL);
	m_canDevice->CanSendNormalData(m_canData->setPdc1_dist_rl(cb->GetCurSel()));
}


void CCanDialog::OnCbnSelchangeComboPdc1DistRml()
{
	CComboBox * cb = (CComboBox *)this->GetDlgItem(IDC_COMBO_PDC1_DIST_RML);
	m_canDevice->CanSendNormalData(m_canData->setPdc1_dist_rml(cb->GetCurSel()));
}


void CCanDialog::OnCbnSelchangeComboPdc1DistRmr()
{
	CComboBox * cb = (CComboBox *)this->GetDlgItem(IDC_COMBO_PDC1_DIST_RMR);
	m_canDevice->CanSendNormalData(m_canData->setPdc1_dist_rmr(cb->GetCurSel()));
}


void CCanDialog::OnCbnSelchangeComboPdc1DistRr()
{
	CComboBox * cb = (CComboBox *)this->GetDlgItem(IDC_COMBO_PDC1_DIST_RR);
	m_canDevice->CanSendNormalData(m_canData->setPdc1_dist_rr(cb->GetCurSel()));
}


void CCanDialog::OnBnClickedCheck1Pdc1SensrFl()
{
	int ret = 0;
	if (IsDlgButtonChecked(IDC_CHECK1_PDC1_SENSR_FL))
	{
		ret = 1;
	}
	m_canDevice->CanSendNormalData(m_canData->setPdc1_sensr_fl(ret));
}


void CCanDialog::OnBnClickedCheck1Pdc1SensrFml()
{
	int ret = 0;
	if (IsDlgButtonChecked(IDC_CHECK1_PDC1_SENSR_FML))
	{
		ret = 1;
	}
	m_canDevice->CanSendNormalData(m_canData->setPdc1_sensr_fml(ret));
}


void CCanDialog::OnBnClickedCheck1Pdc1SensrFmr()
{
	int ret = 0;
	if (IsDlgButtonChecked(IDC_CHECK1_PDC1_SENSR_FMR))
	{
		ret = 1;
	}
	m_canDevice->CanSendNormalData(m_canData->setPdc1_sensr_fmr(ret));
}


void CCanDialog::OnBnClickedCheck1Pdc1SensrFr()
{
	int ret = 0;
	if (IsDlgButtonChecked(IDC_CHECK1_PDC1_SENSR_FR))
	{
		ret = 1;
	}
	m_canDevice->CanSendNormalData(m_canData->setPdc1_sensr_fr(ret));
}


void CCanDialog::OnBnClickedCheckPdc1SensrSys()
{
	int ret = 0;
	if (IsDlgButtonChecked(IDC_CHECK_PDC1_SENSR_SYS))
	{
		ret = 1;
	}
	m_canDevice->CanSendNormalData(m_canData->setPdc1_sensr_system(ret));
}


void CCanDialog::OnBnClickedCheck1Pdc1SensrRl()
{
	int ret = 0;
	if (IsDlgButtonChecked(IDC_CHECK1_PDC1_SENSR_RL))
	{
		ret = 1;
	}
	m_canDevice->CanSendNormalData(m_canData->setPdc1_sensr_rl(ret));
}


void CCanDialog::OnBnClickedCheck1Pdc1SensrRml()
{
	int ret = 0;
	if (IsDlgButtonChecked(IDC_CHECK1_PDC1_SENSR_RML))
	{
		ret = 1;
	}
	m_canDevice->CanSendNormalData(m_canData->setPdc1_sensr_rml(ret));
}


void CCanDialog::OnBnClickedCheck1Pdc1SensrRmr()
{
	int ret = 0;
	if (IsDlgButtonChecked(IDC_CHECK1_PDC1_SENSR_RMR))
	{
		ret = 1;
	}
	m_canDevice->CanSendNormalData(m_canData->setPdc1_sensr_rmr(ret));
}


void CCanDialog::OnBnClickedCheck1Pdc1SensrRr()
{
	int ret = 0;
	if (IsDlgButtonChecked(IDC_CHECK1_PDC1_SENSR_RR))
	{
		ret = 1;
	}
	m_canDevice->CanSendNormalData(m_canData->setPdc1_sensr_rr(ret));
}


void CCanDialog::OnBnClickedCheckIce4SideviewEnable()
{
	int ret = 0;
	if (IsDlgButtonChecked(IDC_CHECK_ICE4_SIDEVIEW_ENABLE))
	{
		ret = 1;
	}
	m_canDevice->CanSendNormalData(m_canData->setIce4_sideViewEnable(ret));
}


void CCanDialog::OnBnClickedCheckIce4PdcviewEnable()
{
	int ret = 0;
	if (IsDlgButtonChecked(IDC_CHECK_ICE4_PDCVIEW_ENABLE))
	{
		ret = 1;
	}
	m_canDevice->CanSendNormalData(m_canData->setIce4_pdcViewDisp(ret));
}


void CCanDialog::OnCbnSelchangeComboIce4Carcolor()
{
	CComboBox * cb = (CComboBox *)this->GetDlgItem(IDC_COMBO_ICE4_CARCOLOR);

	m_canDevice->CanSendNormalData(m_canData->setIce4_carColor(cb->GetCurSel()));
}


void CCanDialog::OnBnClickedButtonIce4Avm()
{
	m_canDevice->CanSendNormalData(m_canData->setIce4_avmKey(1));
}


void CCanDialog::OnBnClickedButtonScrn()
{
	int x, y;
	CString strx, stry;

	m_edit_touch_x.GetWindowText(strx);
	m_edit_touch_y.GetWindowText(stry);

	x = _ttoi(strx);
	y = _ttoi(stry);

	m_canData->setIce4_touchKey_x(x);
	m_canData->setIce4_touchKey_y(y);
	m_canDevice->CanSendNormalData(m_canData->setIce4_touchKey_press(ICE4_TOUCHKEY_PRESS));
	Sleep(30);
	m_canDevice->CanSendNormalData(m_canData->setIce4_touchKey_press(ICE4_TOUCHKEY_NOPRESS));
}


void CCanDialog::OnBnClickedButtonIce4Calib()
{
	m_canDevice->CanSendNormalData(m_canData->setIce4_calibKey(1));
}


void CCanDialog::OnBnClickedRadioIce5()
{
	if (IsDlgButtonChecked(IDC_RADIO_ICE5_800_600))
	{
		m_canDevice->CanSendNormalData(m_canData->setIce5_resolution_screen(ICE5_RESLUTION_800_600));
		m_slider_x.SetRange(0, 800);
		m_slider_y.SetRange(0, 600);
	}

	else if (IsDlgButtonChecked(IDC_RADIO_ICE5_1024_600))
	{
		m_canDevice->CanSendNormalData(m_canData->setIce5_resolution_screen(ICE5_RESLUTION_1024_600));
		m_slider_x.SetRange(0, 1024);
		m_slider_y.SetRange(0, 600);
	}
}


void CCanDialog::OnBnClickedButtonOpencan()
{
	if (!m_canDevice->IsDeviceOpen())
		m_canDevice->TryOpenDevice();

	if (!m_canDevice->IsDeviceOpen())
	{
		(CButton *)this->GetDlgItem(IDC_BUTTON_OPENCAN)->EnableWindow(true);
		(CButton *)this->GetDlgItem(IDC_BUTTON_CLOSECAN)->EnableWindow(false);
	}
	else
	{
		(CButton *)this->GetDlgItem(IDC_BUTTON_OPENCAN)->EnableWindow(false);
		(CButton *)this->GetDlgItem(IDC_BUTTON_CLOSECAN)->EnableWindow(true);
	}
}


void CCanDialog::OnBnClickedButtonClosecan()
{
	if (m_canDevice->IsDeviceOpen())
		m_canDevice->TryCloseDevice();

	if (!m_canDevice->IsDeviceOpen())
	{
		(CButton *)this->GetDlgItem(IDC_BUTTON_OPENCAN)->EnableWindow(true);
		(CButton *)this->GetDlgItem(IDC_BUTTON_CLOSECAN)->EnableWindow(false);
	}
	else
	{
		(CButton *)this->GetDlgItem(IDC_BUTTON_OPENCAN)->EnableWindow(false);
		(CButton *)this->GetDlgItem(IDC_BUTTON_CLOSECAN)->EnableWindow(true);
	}
}


void CCanDialog::OnEnChangeEditAngle()
{
	CString strAngle;
	int angle;
	m_edit_angle.GetWindowText(strAngle);

	angle = _ttoi(strAngle);
	m_canDevice->CanSendNormalData(m_canData->setSas1_steering_angle(angle));
	m_slider_angle.SetPos(angle);
}


void CCanDialog::OnNMCustomdrawSliderAngle(NMHDR *pNMHDR, LRESULT *pResult)
{
	static int i = -1;
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	CString strAngle;
	int angle = m_slider_angle.GetPos();
	if (i != angle)
	{
		strAngle.Format(L"%d", angle);
		m_edit_angle.SetWindowText(strAngle);
		i = angle;
	}
	*pResult = 0;
}



void CCanDialog::OnBnClickedButtonComPort()
{
	this->GetParent()->ShowWindow(SW_SHOW);
}


void CCanDialog::OnBnClickedButtonComPort2()
{
	this->GetParent()->ShowWindow(SW_HIDE);
}


void CCanDialog::OnBnClickedButtonSnd()
{
	ST_PACKET packetBuf;
	CString id, data, cycle;
	BYTE hex[10];

	m_edit_snd_data.GetWindowTextW(data);
	m_edit_send_id.GetWindowTextW(id);
	m_edit_cycle.GetWindowTextW(cycle);

	CMyString::String2Hex(id, hex);
	packetBuf.id = hex[0] << 8 | hex[1];

	CMyString::String2Hex(data, hex);
	for (int i = 0; i < 8; i++)
		packetBuf.data[i] = hex[i];

	packetBuf.tmInterval = _ttoi(cycle);

	packetBuf.enable = 1;

	if (m_canDevice->IsDeviceOpen())
	{
		if (packetBuf.tmInterval)
		{
			m_edit_snd_data.EnableWindow(false);
			m_edit_send_id.EnableWindow(false);
			m_edit_cycle.EnableWindow(false);
			m_btn_send.EnableWindow(false);
			m_edit_send_stop.EnableWindow(true);
		}
		
		m_canDevice->CanSendNormalData(packetBuf);
	}
}


void CCanDialog::OnBnClickedButtonStopsnd()
{
	ST_PACKET packetBuf;
	CString id, data, cycle;
	BYTE hex[10];

	m_edit_snd_data.GetWindowTextW(data);
	m_edit_send_id.GetWindowTextW(id);
	m_edit_cycle.GetWindowTextW(cycle);

	CMyString::String2Hex(id, hex);
	packetBuf.id = hex[0] << 8 | hex[1];

	CMyString::String2Hex(data, hex);
	for (int i = 0; i < 8; i++)
		packetBuf.data[i] = hex[i];

	packetBuf.tmInterval = _ttoi(cycle);

	packetBuf.enable = 0;

	m_canDevice->CanSendNormalData(packetBuf);

	m_btn_send.EnableWindow(true);
	m_edit_send_stop.EnableWindow(false);
	m_edit_snd_data.EnableWindow(true);
	m_edit_send_id.EnableWindow(true);
	m_edit_cycle.EnableWindow(true);
}














//////////
void c_dlg_data_receiver::receive(const VCI_CAN_OBJ * ba, int cb)
{
	CCanDialog * mCanDlg = (CCanDialog *)ptr_canDlg;
	if (mCanDlg == NULL)
		return;
	static int isVideoOn = -1;
	static int isSideViewOn = -1;
	static int isPdcViewOn = -1;
	for (int i = 0; i < cb; i++)
	{
		if (ba->ID == 0x37a)
		{
			if (ba->Data[0] & 0x20 && isVideoOn!=1)
			{
				isVideoOn = 1;
				mCanDlg->m_edit_rcv_videoOnOff.SetWindowTextW(L"目前处于AVM 显示中");
			}
			else if ((ba->Data[0] & 0x20) == 0 && isVideoOn != 0)
			{
				isVideoOn = 0;
				mCanDlg->m_edit_rcv_videoOnOff.SetWindowTextW(L"目前处于导航显示中");
			}

			if (ba->Data[2] & 0x20 && isSideViewOn != 1)
			{
				isSideViewOn = 1;
				mCanDlg->m_edit_rcv_sideview.SetWindowTextW(L"3D侧视功能开关已经打开");
			}
			else if ((ba->Data[2] & 0x20) == 0 && isSideViewOn != 0)
			{
				isSideViewOn = 0;
				mCanDlg->m_edit_rcv_sideview.SetWindowTextW(L"3D侧视功能开关已经关闭");
			}

			if (ba->Data[2] & 0x40 && isPdcViewOn != 1)
			{
				isPdcViewOn = 1;
				mCanDlg->m_edit_pdcview.SetWindowTextW(L"雷达显示开关已经打开");
			}
			else if ((ba->Data[2] & 0x40) == 0 && isPdcViewOn != 0)
			{
				isPdcViewOn = 0;
				mCanDlg->m_edit_pdcview.SetWindowTextW(L"雷达显示开关已经关闭");
			}
		}
	}
}




void CCanDialog::OnNMCustomdrawSliderX(NMHDR *pNMHDR, LRESULT *pResult)
{
	static int i = -1;
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码

	CString strSpd;
	int v = m_slider_x.GetPos();
	if (i != v)
	{
		strSpd.Format(L"%d", v);
		m_edit_touch_x.SetWindowText(strSpd);
		i = v;
	}
	*pResult = 0;
}


void CCanDialog::OnNMCustomdrawSliderY(NMHDR *pNMHDR, LRESULT *pResult)
{
	static int i = -1;
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码

	CString strSpd;
	int v = m_slider_y.GetPos();
	if (i != v)
	{
		strSpd.Format(L"%d", v);
		m_edit_touch_y.SetWindowText(strSpd);
		i = v;
	}
	*pResult = 0;
}
