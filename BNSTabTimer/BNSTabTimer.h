
// BNSTabTimer.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号

// 程序单实例
#define BNSTabTimer_CLASSNAME _T("BNSTabTimer")
#define APPMUTEX _T("Global\\ScanSettings")


// CBNSTabTimerApp:
// 有关此类的实现，请参阅 BNSTabTimer.cpp
//

class CBNSTabTimerApp : public CWinApp
{
public:
	CBNSTabTimerApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	BOOL RestrictOneInstance();
DECLARE_MESSAGE_MAP()
private:
	HANDLE m_hMutex;
};

extern CBNSTabTimerApp theApp;
