
// MySerial.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMySerialApp: 
// �йش����ʵ�֣������ MySerial.cpp
//

class CMySerialApp : public CWinApp
{
public:
	CMySerialApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMySerialApp theApp;