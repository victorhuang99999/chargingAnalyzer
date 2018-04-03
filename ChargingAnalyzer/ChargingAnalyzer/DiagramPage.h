#pragma once
#include "tchart1.h"

// CDiagramPage �Ի���

class CDiagramPage : public CDialogEx
{
	//DECLARE_DYNAMIC(CDiagramPage)

public:
	CDiagramPage(std::vector<std::vector<CString>> data);   // ��׼���캯��
	virtual ~CDiagramPage();

// �Ի�������
	enum { IDD = IDD_DIAGRAM_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CTchart1 m_data;
	std::vector<std::vector<CString>> mData;
	afx_msg void OnBnClickedDrawDiagram();
};