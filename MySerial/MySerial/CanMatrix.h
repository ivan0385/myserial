#pragma once

typedef struct
{
	bool enable;
	int tmInterval; //ms
	int id;
	char data[8];
}ST_PACKET;

typedef struct
{
	int bytes; // 在哪个字节
	int value; 
	int mask;  
}ST_ITEM;

enum
{
	BCM1_IGN_OFF,
	BCM1_IGN_ACC = 0x04,
	BCM1_IGN_ON = 0x08,
	BCM1_IGN_START = 0x0c
};

enum
{
	BCM1_LAMP_OFF,
	BCM1_LAMP_TURNLEFT = 0x10,
	BCM1_LAMP_TURNRIGHT = 0x20,
	BCM1_LAMP_TURNBOTH = 0x30
};

enum
{
	IC1_REVERSE_OFF,
	IC1_REVERSE_GEAR = 0x40,
};

enum
{
	ICE4_TOUCHKEY_NOPRESS,
	ICE4_TOUCHKEY_PRESS = 0x10,
	ICE4_TOUCHKEY_INVALID = 0x30
};

enum
{
	ICE5_RESLUTION_INVALID,
	ICE5_RESLUTION_800_600 = 0x10,
	ICE5_RESLUTION_1024_600 = 0x20
};

class CanMatrix
{
public:
	CanMatrix();
	~CanMatrix();



	ST_PACKET m_snd_bcm1;
	ST_ITEM m_snd_bcm1_ign;	
	ST_PACKET setBcm1_Ign(int status);
	ST_ITEM m_snd_bcm1_lamp; 	
	ST_PACKET setBcm1_lamp(int status);
	ST_PACKET buildBcm1();

	ST_PACKET m_snd_ic1;
	ST_ITEM m_snd_ic1_reverse;
	ST_PACKET setIc1_reverse(int status);
	ST_PACKET buildIc1();

	ST_PACKET m_snd_abs1;
	ST_ITEM m_snd_abs1_speed;
	ST_PACKET setAbs1_speed(int status);
	ST_PACKET buildAbs1();

	ST_PACKET m_snd_pdc1;
	// The min distance detected from the Sensor
	ST_ITEM m_snd_pdc1_dist_fl; //The min distance detected from the Front Left Sensor
	ST_PACKET setPdc1_dist_fl(int value);
	ST_ITEM m_snd_pdc1_dist_fr;
	ST_PACKET setPdc1_dist_fr(int value);
	ST_ITEM m_snd_pdc1_dist_fml; // front middle left
	ST_PACKET setPdc1_dist_fml(int value);
	ST_ITEM m_snd_pdc1_dist_fmr;
	ST_PACKET setPdc1_dist_fmr(int value);
	ST_ITEM m_snd_pdc1_dist_rl; // rear left
	ST_PACKET setPdc1_dist_rl(int value);
	ST_ITEM m_snd_pdc1_dist_rr;
	ST_PACKET setPdc1_dist_rr(int value);
	ST_ITEM m_snd_pdc1_dist_rml; // rear middle left or rear middel
	ST_PACKET setPdc1_dist_rml(int value);
	ST_ITEM m_snd_pdc1_dist_rmr;
	ST_PACKET setPdc1_dist_rmr(int value);
	// Sensor Normal or Fault
	ST_ITEM m_snd_pdc1_sensr_fl; //The Front Left Sensor Normal or Fault
	ST_PACKET setPdc1_sensr_fl(int value);
	ST_ITEM m_snd_pdc1_sensr_fr;
	ST_PACKET setPdc1_sensr_fr(int value);
	ST_ITEM m_snd_pdc1_sensr_fml; // front middle left
	ST_PACKET setPdc1_sensr_fml(int value);
	ST_ITEM m_snd_pdc1_sensr_fmr;
	ST_PACKET setPdc1_sensr_fmr(int value);
	ST_ITEM m_snd_pdc1_sensr_rl; // rear left
	ST_PACKET setPdc1_sensr_rl(int value);
	ST_ITEM m_snd_pdc1_sensr_rr;
	ST_PACKET setPdc1_sensr_rr(int value);
	ST_ITEM m_snd_pdc1_sensr_rml; // rear middle left or rear middel
	ST_PACKET setPdc1_sensr_rml(int value);
	ST_ITEM m_snd_pdc1_sensr_rmr;
	ST_PACKET setPdc1_sensr_rmr(int value);
	//Indication of shortest distance of senors from object.雷达与障碍物最短距离的指示信息
	ST_ITEM m_snd_pdc1_dist_min;
	ST_PACKET setPdc1_dist_min(int value);
	// Parking Distance Control Fault Status
	ST_ITEM m_snd_pdc1_sensr_system;
	ST_PACKET setPdc1_sensr_system(int value);
	//The Number of radar
	ST_ITEM m_snd_pdc1_number;
	ST_PACKET setPdc1_number(int value);
	ST_PACKET buildPdc1();


	ST_PACKET m_snd_ice4;
	ST_ITEM m_snd_ice4_sideViewEnable;
	ST_ITEM m_snd_ice4_pdcViewDisp;
	ST_ITEM m_snd_ice4_carColor;
	ST_ITEM m_snd_ice4_avmKey;
	ST_ITEM m_snd_ice4_calibKey;
	ST_ITEM m_snd_ice4_touchKey_press;
	ST_ITEM m_snd_ice4_touchKey_x;
	ST_ITEM m_snd_ice4_touchKey_y;
	ST_PACKET setIce4_sideViewEnable(int value);
	ST_PACKET setIce4_pdcViewDisp(int value);
	ST_PACKET setIce4_carColor(int value);
	ST_PACKET setIce4_avmKey(int value);
	ST_PACKET setIce4_calibKey(int value);
	ST_PACKET setIce4_touchKey_press(int value);
	void setIce4_touchKey_x(int value);
	void setIce4_touchKey_y(int value);
	ST_PACKET buildIce4();


	ST_PACKET m_snd_ice5;
	ST_ITEM m_snd_ice5_resolution_screen;
	ST_PACKET setIce5_resolution_screen(int value);
	ST_PACKET buildIce5();


	ST_PACKET m_snd_sas1;
	ST_ITEM m_snd_sas1_steering_angle;
	ST_PACKET setSas1_steering_angle(int value);
	ST_PACKET buildSas1();
};

