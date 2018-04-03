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

CDiagramPage::CDiagramPage(std::vector<std::vector<CString>> data) : CDialogEx(CDiagramPage::IDD)
{
	mData = data;
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
	ON_BN_CLICKED(IDC_DRAW_DIAGRAM, &CDiagramPage::OnBnClickedDrawDiagram)
END_MESSAGE_MAP()

void CDiagramPage::OnBnClickedDrawDiagram()
{
	CSeries lineSeries1 = (CSeries)m_data.Series(0);
	lineSeries1.Clear();
	for (int i = 0; i < mData[113].size(); i++)
    {
        lineSeries1.AddXY((double)i,  _wtof(mData[113][i])/(-1000000),NULL,NULL);
    }

	CSeries lineSeries2 = (CSeries)m_data.Series(1);
	lineSeries2.Clear();
	for (int i = 0; i < mData[113].size(); i++)
    {
        lineSeries2.AddXY((double)i,  _wtof(mData[106][i])/1000000,NULL,NULL);
    }
}
