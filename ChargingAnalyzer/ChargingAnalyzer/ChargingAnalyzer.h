
// ChargingAnalyzer.h : ChargingAnalyzer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "charDataAnalyzer.h"
#include "DiagramPage.h"

class CChargingAnalyzerApp : public CWinAppEx
{
public:
	CChargingAnalyzerApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual void OnFileOpen();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	charDataAnalyzer m_charDataAnalyzer;


	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


	afx_msg void OnShowDiagram();
};

extern CChargingAnalyzerApp theApp;
