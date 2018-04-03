// DiagramPage.cpp : 实现文件
//

#include "stdafx.h"
#include "ChargingAnalyzer.h"
#include "DiagramPage.h"
#include "afxdialogex.h"
#include <stdlib.h>
#include "CSeries.h"
// CDiagramPage 对话框

//IMPLEMENT_DYNAMIC(CDiagramPage, CDialog)

CDiagramPage::CDiagramPage(charDataAnalyzer d_charDataAnalyzer) : CDialogEx(CDiagramPage::IDD)
{
	m_charDataAnalyzer = d_charDataAnalyzer;
}

CDiagramPage::~CDiagramPage()
{
}

void CDiagramPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART1, m_data);
}

BEGIN_MESSAGE_MAP(CDiagramPage, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CDiagramPage::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CDiagramPage::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CDiagramPage::OnBnClickedCheck3)
END_MESSAGE_MAP()

void CDiagramPage::OnBnClickedCheck1()
{
	CSeries lineSeries = (CSeries)m_data.Series(0);
	lineSeries.Clear();
	int state =((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	if(state)
	{
		for (int i = 0; i < (int)m_charDataAnalyzer.mCurrentNowData.size(); i++)
		{
			lineSeries.AddXY((double)i, m_charDataAnalyzer.mCurrentNowData[i],NULL,NULL);
		}
	}
}


void CDiagramPage::OnBnClickedCheck2()
{
	CSeries lineSeries = (CSeries)m_data.Series(1);
	lineSeries.Clear();
	int state =((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck();
	if(state)
	{
		for (int i = 0; i < (int)m_charDataAnalyzer.mData[113].size(); i++)
		{
			lineSeries.AddXY((double)i,  m_charDataAnalyzer.mCurrentExpectData[i],NULL,NULL);
		}
	}
}


void CDiagramPage::OnBnClickedCheck3()
{
	CSeries lineSeries = (CSeries)m_data.Series(2);
	lineSeries.Clear();
	int state =((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck();
	if(state)
	{
		for (int i = 0; i < (int)m_charDataAnalyzer.mVoltageNowData.size(); i++)
		{
			lineSeries.AddXY((double)i, m_charDataAnalyzer.mVoltageNowData[i],NULL,NULL);
		}
	}
}
