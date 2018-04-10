#pragma once
#include "tchart1.h"

// CDiagramPage �Ի���

class CDiagramPage : public CDialogEx
{
	//DECLARE_DYNAMIC(CDiagramPage)

public:
	CDiagramPage(charDataAnalyzer d_charDataAnalyzer);   // ��׼���캯��
	virtual ~CDiagramPage();

// �Ի�������
	enum { IDD = IDD_DIAGRAM_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CTchart1 m_data;
	charDataAnalyzer m_charDataAnalyzer;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedButton1();
};