
// ChargingAnalyzer.h : ChargingAnalyzer 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "charDataAnalyzer.h"
#include "DiagramPage.h"

class CChargingAnalyzerApp : public CWinAppEx
{
public:
	CChargingAnalyzerApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnFileOpen();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	charDataAnalyzer m_charDataAnalyzer;


	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


	afx_msg void OnShowDiagram();
	afx_msg void OnConnectPhone();
};

extern CChargingAnalyzerApp theApp;
