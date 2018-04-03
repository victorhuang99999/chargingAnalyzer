#pragma once
#include "tchart1.h"

// CDiagramPage 对话框

class CDiagramPage : public CDialogEx
{
	//DECLARE_DYNAMIC(CDiagramPage)

public:
	CDiagramPage(charDataAnalyzer d_charDataAnalyzer);   // 标准构造函数
	virtual ~CDiagramPage();

// 对话框数据
	enum { IDD = IDD_DIAGRAM_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
protected:
	DECLARE_MESSAGE_MAP()
public:
	CTchart1 m_data;
	charDataAnalyzer m_charDataAnalyzer;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
};