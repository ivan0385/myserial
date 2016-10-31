#include "stdafx.h"
#include "CanMatrix.h"


CanMatrix::CanMatrix()
{
	// bcm1 报文
	m_snd_bcm1 = { 
		true,
		100,
		0x180,
		{ 0, }
	};
	m_snd_bcm1_ign = {
		2,
		0,
		0x0C
	};
	m_snd_bcm1_lamp = {
		1,
		0,
		0x30
	};


	// ic1 报文
	m_snd_ic1 = {
		true,
		20,
		0x149,
		{ 0, }
	};
	m_snd_ic1_reverse = {
		0,
		0,
		0x40
	};


	//
	// ic1 报文
	m_snd_abs1 = {
		true,
		20,
		0x200,
		{ 0, }
	};
	m_snd_abs1_speed = {
		1,
		0,
		0xfff8
	};


	// pdc1报文
	m_snd_pdc1 = {
		true,
		100,
		0x260,
		{ 0, }
	};
	// Sensor Normal or Fault
	m_snd_pdc1_sensr_fl = {
		0,
		0,
		0x1
	};
	m_snd_pdc1_sensr_fr = {
		0,
		0,
		0x2
	};
	m_snd_pdc1_sensr_fml = {
		0,
		0,
		0x4
	};
	m_snd_pdc1_sensr_fmr = {
		0,
		0,
		0x8
	};
	m_snd_pdc1_sensr_rl = {
		0,
		0,
		0x10
	};
	m_snd_pdc1_sensr_rr = {
		0,
		0,
		0x80
	};
	m_snd_pdc1_sensr_rml = {
		0,
		0,
		0x20
	};
	m_snd_pdc1_sensr_rmr = {
		0,
		0,
		0x40
	};
	// Parking Distance Control Fault Status
	m_snd_pdc1_sensr_system = {
		1,
		0,
		0x4
	};
	// The min distance detected from the Sensor
	m_snd_pdc1_dist_fl = {
		2,
		0,
		0x0f
	};
	m_snd_pdc1_dist_fr = {
		2,
		0,
		0xf0
	};
	m_snd_pdc1_dist_fml = {
		3,
		0,
		0x0f
	};
	m_snd_pdc1_dist_fmr = {
		3,
		0,
		0xf0
	};
	m_snd_pdc1_dist_rl = {
		4,
		0,
		0x0f
	};
	m_snd_pdc1_dist_rml = {
		4,
		0,
		0xf0
	};
	m_snd_pdc1_dist_rmr = {
		5,
		0,
		0x0f
	};
	m_snd_pdc1_dist_rr = {
		5,
		0,
		0xf0
	};	
	//Indication of shortest distance of senors from object.雷达与障碍物最短距离的指示信息
	m_snd_pdc1_dist_min = {
		6,
		0,
		0x0e
	};	
	//The Number of radar
	m_snd_pdc1_number = {
		7,
		0,
		0x7
	};


	// ice4 报文
	m_snd_ice4 = {
		true,
		0,
		0x381,
		{ 0, }
	};
	m_snd_ice4_sideViewEnable = {
		0,
		0,
		0x6
	};
	m_snd_ice4_pdcViewDisp = {
		0,
		0,
		0x18
	};
	m_snd_ice4_carColor = {
		0,
		0,
		0xe0
	};
	m_snd_ice4_avmKey = {
		1,
		0,
		0x1
	};
	m_snd_ice4_calibKey = {
		1,
		0,
		0x4
	};
	m_snd_ice4_touchKey_press = {
		1,
		0,
		0x30
	};
	m_snd_ice4_touchKey_x = {
		2,
		0,
		0xfff0
	};
	m_snd_ice4_touchKey_y = {
		4,
		0,
		0xffe0
	};


	// ice5 报文
	m_snd_ice5 = {
		true,
		0,
		0x3b0,
		{ 0, }
	};
	m_snd_ice5_resolution_screen = {
		1,
		0,
		0xf0
	};


	//sas1报文
	m_snd_sas1 = {
		true,
		20,
		0x300,
		{ 0,1,0 ,}
	};
	m_snd_sas1_steering_angle = {
		3,
		0,
		0xffff
	};
}


CanMatrix::~CanMatrix()
{
}


ST_PACKET CanMatrix::setBcm1_Ign(int status)
{
	m_snd_bcm1_ign.value = status;
	return buildBcm1();
}
ST_PACKET CanMatrix::setBcm1_lamp(int status)
{
	m_snd_bcm1_lamp.value = status;
	return buildBcm1();
}
ST_PACKET CanMatrix::buildBcm1()
{
	m_snd_bcm1.data[m_snd_bcm1_ign.bytes] = m_snd_bcm1.data[m_snd_bcm1_ign.bytes] & (~m_snd_bcm1_ign.mask) | m_snd_bcm1_ign.value;
	m_snd_bcm1.data[m_snd_bcm1_lamp.bytes] = m_snd_bcm1.data[m_snd_bcm1_lamp.bytes] & (~m_snd_bcm1_lamp.mask) | m_snd_bcm1_lamp.value;
	return m_snd_bcm1;
}


ST_PACKET CanMatrix::setIc1_reverse(int status)
{
	m_snd_ic1_reverse.value = status;
	return buildIc1();
}
ST_PACKET CanMatrix::buildIc1()
{
	m_snd_ic1.data[m_snd_ic1_reverse.bytes] = m_snd_ic1.data[m_snd_ic1_reverse.bytes] & (~m_snd_ic1_reverse.mask) | m_snd_ic1_reverse.value;
	return m_snd_ic1;
}


ST_PACKET CanMatrix::setAbs1_speed(int status)
{
	unsigned long speed = (unsigned long) (status / 0.05625);
	m_snd_abs1_speed.value = speed << 3;
	return buildAbs1();
}
ST_PACKET CanMatrix::buildAbs1()
{	
	m_snd_abs1.data[m_snd_abs1_speed.bytes] = (unsigned char)(m_snd_abs1_speed.value >> 8);
	m_snd_abs1.data[m_snd_abs1_speed.bytes + 1] = m_snd_abs1.data[m_snd_abs1_speed.bytes + 1] & (~m_snd_abs1_speed.mask) + (unsigned char)m_snd_ic1_reverse.value;
	return m_snd_abs1;
}

ST_PACKET CanMatrix::setPdc1_dist_fl(int value)
{
	m_snd_pdc1_dist_fl.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_dist_fr(int value)
{
	m_snd_pdc1_dist_fr.value = value<<4;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_dist_fml(int value)
{
	m_snd_pdc1_dist_fml.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_dist_fmr(int value)
{
	m_snd_pdc1_dist_fmr.value = value<<4;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_dist_rl(int value)
{
	m_snd_pdc1_dist_rl.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_dist_rr(int value)
{
	m_snd_pdc1_dist_rr.value = value<<4;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_dist_rml(int value)
{
	m_snd_pdc1_dist_rml.value = value<<4;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_dist_rmr(int value)
{
	m_snd_pdc1_dist_rmr.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_sensr_fl(int value)
{
	if (value)
		value = m_snd_pdc1_sensr_fl.mask;
	m_snd_pdc1_sensr_fl.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_sensr_fr(int value)
{
	if (value)
		value = m_snd_pdc1_sensr_fr.mask;
	m_snd_pdc1_sensr_fr.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_sensr_fml(int value)
{
	if (value)
		value = m_snd_pdc1_sensr_fml.mask;
	m_snd_pdc1_sensr_fml.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_sensr_fmr(int value)
{
	if (value)
		value = m_snd_pdc1_sensr_fmr.mask;
	m_snd_pdc1_sensr_fmr.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_sensr_rl(int value)
{
	if (value)
		value = m_snd_pdc1_sensr_rl.mask;
	m_snd_pdc1_sensr_rl.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_sensr_rr(int value)
{
	if (value)
		value = m_snd_pdc1_sensr_rr.mask;
	m_snd_pdc1_sensr_rr.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_sensr_rml(int value)
{
	if (value)
		value = m_snd_pdc1_sensr_rml.mask;
	m_snd_pdc1_sensr_rml.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_sensr_rmr(int value)
{
	if (value)
		value = m_snd_pdc1_sensr_rmr.mask;
	m_snd_pdc1_sensr_rmr.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_dist_min(int value)
{
	m_snd_pdc1_dist_min.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_sensr_system(int value)
{
	if (value)
		value = m_snd_pdc1_sensr_system.mask;
	m_snd_pdc1_sensr_system.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::setPdc1_number(int value)
{
	/*
		0x0: Rear 3
		0x1 : Rear 4
		0x2 : Rear 3 and Front 2
		0x3 : Rear 4 and Front 2
		0x4 : Rear 4 and Front 4
	*/
	m_snd_pdc1_number.value = value;
	return buildPdc1();
}
ST_PACKET CanMatrix::buildPdc1()
{
	m_snd_pdc1.data[m_snd_pdc1_dist_fl.bytes] = m_snd_pdc1.data[m_snd_pdc1_dist_fl.bytes] & (~m_snd_pdc1_dist_fl.mask) | m_snd_pdc1_dist_fl.value;
	m_snd_pdc1.data[m_snd_pdc1_dist_fr.bytes] = m_snd_pdc1.data[m_snd_pdc1_dist_fr.bytes] & (~m_snd_pdc1_dist_fr.mask) | m_snd_pdc1_dist_fr.value;
	m_snd_pdc1.data[m_snd_pdc1_dist_fml.bytes] = m_snd_pdc1.data[m_snd_pdc1_dist_fml.bytes] & (~m_snd_pdc1_dist_fml.mask) | m_snd_pdc1_dist_fml.value;
	m_snd_pdc1.data[m_snd_pdc1_dist_fmr.bytes] = m_snd_pdc1.data[m_snd_pdc1_dist_fmr.bytes] & (~m_snd_pdc1_dist_fmr.mask) | m_snd_pdc1_dist_fmr.value;
	m_snd_pdc1.data[m_snd_pdc1_dist_rl.bytes] = m_snd_pdc1.data[m_snd_pdc1_dist_rl.bytes] & (~m_snd_pdc1_dist_rl.mask) | m_snd_pdc1_dist_rl.value;
	m_snd_pdc1.data[m_snd_pdc1_dist_rr.bytes] = m_snd_pdc1.data[m_snd_pdc1_dist_rr.bytes] & (~m_snd_pdc1_dist_rr.mask) | m_snd_pdc1_dist_rr.value;
	m_snd_pdc1.data[m_snd_pdc1_dist_rml.bytes] = m_snd_pdc1.data[m_snd_pdc1_dist_rml.bytes] & (~m_snd_pdc1_dist_rml.mask) | m_snd_pdc1_dist_rml.value;
	m_snd_pdc1.data[m_snd_pdc1_dist_rmr.bytes] = m_snd_pdc1.data[m_snd_pdc1_dist_rmr.bytes] & (~m_snd_pdc1_dist_rmr.mask) | m_snd_pdc1_dist_rmr.value;
	m_snd_pdc1.data[m_snd_pdc1_sensr_fl.bytes] = m_snd_pdc1.data[m_snd_pdc1_sensr_fl.bytes] & (~m_snd_pdc1_sensr_fl.mask) | m_snd_pdc1_sensr_fl.value;
	m_snd_pdc1.data[m_snd_pdc1_sensr_fr.bytes] = m_snd_pdc1.data[m_snd_pdc1_sensr_fr.bytes] & (~m_snd_pdc1_sensr_fr.mask) | m_snd_pdc1_sensr_fr.value;
	m_snd_pdc1.data[m_snd_pdc1_sensr_fml.bytes] = m_snd_pdc1.data[m_snd_pdc1_sensr_fml.bytes] & (~m_snd_pdc1_sensr_fml.mask) | m_snd_pdc1_sensr_fml.value;
	m_snd_pdc1.data[m_snd_pdc1_sensr_fmr.bytes] = m_snd_pdc1.data[m_snd_pdc1_sensr_fmr.bytes] & (~m_snd_pdc1_sensr_fmr.mask) | m_snd_pdc1_sensr_fmr.value;
	m_snd_pdc1.data[m_snd_pdc1_sensr_rl.bytes] = m_snd_pdc1.data[m_snd_pdc1_sensr_rl.bytes] & (~m_snd_pdc1_sensr_rl.mask) | m_snd_pdc1_sensr_rl.value;
	m_snd_pdc1.data[m_snd_pdc1_sensr_rr.bytes] = m_snd_pdc1.data[m_snd_pdc1_sensr_rr.bytes] & (~m_snd_pdc1_sensr_rr.mask) | m_snd_pdc1_sensr_rr.value;
	m_snd_pdc1.data[m_snd_pdc1_sensr_rml.bytes] = m_snd_pdc1.data[m_snd_pdc1_sensr_rml.bytes] & (~m_snd_pdc1_sensr_rml.mask) | m_snd_pdc1_sensr_rml.value;
	m_snd_pdc1.data[m_snd_pdc1_sensr_rmr.bytes] = m_snd_pdc1.data[m_snd_pdc1_sensr_rmr.bytes] & (~m_snd_pdc1_sensr_rmr.mask) | m_snd_pdc1_sensr_rmr.value;
	m_snd_pdc1.data[m_snd_pdc1_dist_min.bytes] = m_snd_pdc1.data[m_snd_pdc1_dist_min.bytes] & (~m_snd_pdc1_dist_min.mask) | m_snd_pdc1_dist_min.value;
	m_snd_pdc1.data[m_snd_pdc1_sensr_system.bytes] = m_snd_pdc1.data[m_snd_pdc1_sensr_system.bytes] & (~m_snd_pdc1_sensr_system.mask) | m_snd_pdc1_sensr_system.value;
	m_snd_pdc1.data[m_snd_pdc1_number.bytes] = m_snd_pdc1.data[m_snd_pdc1_number.bytes] & (~m_snd_pdc1_number.mask) | m_snd_pdc1_number.value;
	return m_snd_pdc1;
}


ST_PACKET CanMatrix::setIce4_sideViewEnable(int value)
{
	if (value)
		value = 0x2;
	m_snd_ice4_sideViewEnable.value = value;
	m_snd_ice4_calibKey.value = 0;
	m_snd_ice4_avmKey.value = 0;
	m_snd_ice4_touchKey_press.value = m_snd_ice4_touchKey_press.mask;
	return buildIce4();
}
ST_PACKET CanMatrix::setIce4_pdcViewDisp(int value)
{
	if (value)
		value = 0x8;
	m_snd_ice4_pdcViewDisp.value = value;
	m_snd_ice4_calibKey.value = 0;
	m_snd_ice4_avmKey.value = 0;
	m_snd_ice4_touchKey_press.value = m_snd_ice4_touchKey_press.mask;
	return buildIce4();
}
ST_PACKET CanMatrix::setIce4_carColor(int value)
{
	switch (value)
	{
	case 0:
		value = 0x0;
		break;
	case 1:
		value = 0x20;
		break;
	case 2:
		value = 0x40;
		break;
	case 3:
		value = 0x60;
		break;
	case 4:
		value = 0x80;
		break;
	}
	m_snd_ice4_carColor.value = value;
	return buildIce4();
}
ST_PACKET CanMatrix::setIce4_avmKey(int value)
{
	if (value)
		value = m_snd_ice4_avmKey.mask;
	m_snd_ice4_avmKey.value = value;
	m_snd_ice4_calibKey.value = 0;
	m_snd_ice4_touchKey_press.value = m_snd_ice4_touchKey_press.mask;
	return buildIce4();
}
ST_PACKET CanMatrix::setIce4_calibKey(int value)
{
	if (value)
		value = m_snd_ice4_calibKey.mask;
	m_snd_ice4_calibKey.value = value;
	m_snd_ice4_avmKey.value = 0;
	m_snd_ice4_touchKey_press.value = m_snd_ice4_touchKey_press.mask;
	return buildIce4();
}
ST_PACKET CanMatrix::setIce4_touchKey_press(int value)
{
	m_snd_ice4_avmKey.value = 0;
	m_snd_ice4_calibKey.value = 0;

	m_snd_ice4_touchKey_press.value = value;
	return buildIce4();
}
void CanMatrix::setIce4_touchKey_x(int value)
{
	m_snd_ice4_touchKey_x.value = value;
}
void CanMatrix::setIce4_touchKey_y(int value)
{
	m_snd_ice4_touchKey_y.value = value;
}
ST_PACKET CanMatrix::buildIce4()
{
	m_snd_ice4.data[m_snd_ice4_sideViewEnable.bytes] = m_snd_ice4.data[m_snd_ice4_sideViewEnable.bytes] & (~m_snd_ice4_sideViewEnable.mask) | m_snd_ice4_sideViewEnable.value;
	m_snd_ice4.data[m_snd_ice4_pdcViewDisp.bytes] = m_snd_ice4.data[m_snd_ice4_pdcViewDisp.bytes] & (~m_snd_ice4_pdcViewDisp.mask) | m_snd_ice4_pdcViewDisp.value;
	m_snd_ice4.data[m_snd_ice4_carColor.bytes] = m_snd_ice4.data[m_snd_ice4_carColor.bytes] & (~m_snd_ice4_carColor.mask) | m_snd_ice4_carColor.value;
	m_snd_ice4.data[m_snd_ice4_avmKey.bytes] = m_snd_ice4.data[m_snd_ice4_avmKey.bytes] & (~m_snd_ice4_avmKey.mask) | m_snd_ice4_avmKey.value;
	m_snd_ice4.data[m_snd_ice4_calibKey.bytes] = m_snd_ice4.data[m_snd_ice4_calibKey.bytes] & (~m_snd_ice4_calibKey.mask) | m_snd_ice4_calibKey.value;
	m_snd_ice4.data[m_snd_ice4_touchKey_press.bytes] = m_snd_ice4.data[m_snd_ice4_touchKey_press.bytes] & (~m_snd_ice4_touchKey_press.mask) | m_snd_ice4_touchKey_press.value;
	
	m_snd_ice4.data[m_snd_ice4_touchKey_x.bytes] = m_snd_ice4.data[m_snd_ice4_touchKey_x.bytes] & (~(m_snd_ice4_touchKey_x.mask>>8)) | (m_snd_ice4_touchKey_x.value >>8);
	m_snd_ice4.data[m_snd_ice4_touchKey_x.bytes + 1] = m_snd_ice4.data[m_snd_ice4_touchKey_x.bytes + 1] & (~m_snd_ice4_touchKey_x.mask) | (m_snd_ice4_touchKey_x.value & 0xff);
	m_snd_ice4.data[m_snd_ice4_touchKey_y.bytes] = m_snd_ice4.data[m_snd_ice4_touchKey_y.bytes] & (~(m_snd_ice4_touchKey_y.mask >> 8)) | (m_snd_ice4_touchKey_y.value >> 8);
	m_snd_ice4.data[m_snd_ice4_touchKey_y.bytes + 1] = m_snd_ice4.data[m_snd_ice4_touchKey_y.bytes + 1] & (~m_snd_ice4_touchKey_y.mask) | (m_snd_ice4_touchKey_y.value & 0xff);
	return m_snd_ice4;
}

ST_PACKET CanMatrix::setIce5_resolution_screen(int value)
{
	m_snd_ice5_resolution_screen.value = value;
	return buildIce5();
}
ST_PACKET CanMatrix::buildIce5()
{
	m_snd_ice5.data[m_snd_ice5_resolution_screen.bytes] = m_snd_ice5.data[m_snd_ice5_resolution_screen.bytes] & (~m_snd_ice5_resolution_screen.mask) | m_snd_ice5_resolution_screen.value;
	return m_snd_ice5;
}


ST_PACKET CanMatrix::setSas1_steering_angle(int value)
{
	m_snd_sas1_steering_angle.value = value;
	return buildSas1();
}

ST_PACKET CanMatrix::buildSas1()
{
	m_snd_sas1.data[m_snd_sas1_steering_angle.bytes] = m_snd_sas1.data[m_snd_sas1_steering_angle.bytes] & (~m_snd_sas1_steering_angle.mask) | (m_snd_sas1_steering_angle.value>>8);
	m_snd_sas1.data[m_snd_sas1_steering_angle.bytes+1] = m_snd_sas1.data[m_snd_sas1_steering_angle.bytes+1] & (~m_snd_sas1_steering_angle.mask) | (m_snd_sas1_steering_angle.value &0xff);
	return m_snd_sas1;
}