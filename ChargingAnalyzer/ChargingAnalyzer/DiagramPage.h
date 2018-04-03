#pragma once
#include "tchart1.h"

// CDiagramPage 对话框

class CDiagramPage : public CDialogEx
{
	//DECLARE_DYNAMIC(CDiagramPage)

public:
	CDiagramPage(std::vector<std::vector<CString>> data);   // 标准构造函数
	virtual ~CDiagramPage();

// 对话框数据
	enum { IDD = IDD_DIAGRAM_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
protected:
	DECLARE_MESSAGE_MAP()
public:
	CTchart1 m_data;
	std::vector<std::vector<CString>> mData;
	afx_msg void OnBnClickedDrawDiagram();
};