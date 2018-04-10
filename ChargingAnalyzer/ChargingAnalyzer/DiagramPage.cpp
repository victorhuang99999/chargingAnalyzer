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
	ON_BN_CLICKED(IDC_BUTTON1, &CDiagramPage::OnBnClickedButton1)
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


void CDiagramPage::OnBnClickedButton1()
{
    // TODO: Add extra validation here  
    SECURITY_ATTRIBUTES sa;  
    HANDLE hRead,hWrite;  
  
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);  
    sa.lpSecurityDescriptor = NULL;  
    sa.bInheritHandle = TRUE;  
  
    if(!CreatePipe(&hRead,&hWrite,&sa,0))  
    {  
        MessageBox("CreatePipe Failed");  
        return;  
    }  
  
    STARTUPINFO si;  
    PROCESS_INFORMATION pi;  
  
    ZeroMemory(&si,sizeof(STARTUPINFO));  
    si.cb = sizeof(STARTUPINFO);  
    GetStartupInfo(&si);  
    si.hStdError = hWrite;  
    si.hStdOutput = hWrite;  
    si.wShowWindow = SW_HIDE;  
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;  
  
    char cmdline[CMD_COMMAND_COUNT_MAX];  
    CString tmp,stredit2;  
    stredit2 = "adb shell";
    tmp.Format("cmd /C %s",stredit2);  
    sprintf_s(cmdline,CMD_COMMAND_COUNT_MAX,"%s",tmp);  
  
    if(!CreateProcess(NULL,cmdline,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))  
    {  
        MessageBox("CreateProcess failed!");  
        return;  
    }  
    CloseHandle(hWrite);  
  
    char buffer[4096] = {0};  
    CString strOutput;  
    DWORD bytesRead;  
  
    while(1)  
    {  
        if(NULL == ReadFile(hRead,buffer,4095,&bytesRead,NULL))  
        {  
           break;  
        }  
        strOutput += buffer;  
        //SetDlgItemText(IDC_EDIT_TEXT,strOutput);  
        UpdateWindow();  
        Sleep(1000);  
    }  
    CloseHandle(hRead);  
}
