#include "StdAfx.h"
#include "charDataAnalyzer.h"


charDataAnalyzer::charDataAnalyzer(void)
{
	readNodeConfigFromConfigFile();
	readExpectCurrentConfigFromFile();
}


charDataAnalyzer::~charDataAnalyzer(void)
{
}

//处理数据进程
int charDataAnalyzer::dataProcess(CString path)
{
	CStdioFile file;
	if (!file.Open(path, CFile::modeRead))
	{  
		return 1;
	}
	clearData();
	CString strValue = "";
	CString* strSplit;
	mData.resize(m_data_count);
	int iSubStrs;
	while(file.ReadString(strValue))
	{
		
		if(getDataType(strValue) == LINE_TYPE_DATA)//判断是否为数据
		{
			strSplit = SplitString(strValue,',',iSubStrs);
			for(int i = 0;i < m_data_count; i++ )
			{
				mData[i].push_back(strSplit[i]);
			}
		}
	}
	file.Close();
	if(mData[0].size())
	{
		mCurrentNowData = currentNowProcess();
		mCurrentExpectData = currentExpectProcess();
		mVoltageNowData = voltageNowProcess();
	}
	return 0;
}

//清除数据
void charDataAnalyzer::clearData()
{
	mData.clear();
	mCurrentNowData.clear();
	mCurrentExpectData.clear();
	mVoltageNowData.clear();
}

//判断数据行类型
int charDataAnalyzer::getDataType(CString str){
	if(str.IsEmpty())
		return LINE_TYPE_NONE;
	if(str[0]>='0' && str[0]<='9')
		return LINE_TYPE_DATA;
	if(strstr(str,"TimeStamp"))
		return LINE_TYPE_CONFIG;
	else
		return LINE_TYPE_NONE;
}

//获得当前电流进程
std::vector<float> charDataAnalyzer::currentNowProcess()
{
	std::vector<float> nowData;
	for(int i = 0; i < (int)mData[0].size(); i++){
		nowData.push_back((float)atof(mData[getNodeIndex(_T(NC_BATTERY_CURRENT_NOW))][i])/(-MILLI));
	}
	return nowData;
}

//获得当前电压进程
std::vector<float> charDataAnalyzer::voltageNowProcess()
{
	std::vector<float> nowData;
	for(int i = 0; i < (int)mData[0].size(); i++){
		nowData.push_back((float)atof(mData[getNodeIndex(_T(NC_BATTERY_VOLTAGE_NOW))][i])/MILLI);
	}
	return nowData;
}

//获得预期电流进程
std::vector<float> charDataAnalyzer::currentExpectProcess()
{
	std::vector<float> expectData;
	for(int i = 0; i < (int)mData[0].size(); i++){
		expectData.push_back(getCurrentExpectSingle(i));
	}
	return expectData;
}

//读取config文件节点配置
void charDataAnalyzer::readNodeConfigFromConfigFile()
{
	CStdioFile file;
	if (!file.Open(getFilePath(NODE_CONFIG_FILE_PATH), CFile::modeRead))
	{  
		return;
	}
	CString strValue = "";
	file.ReadString(strValue);
	m_nodeConfig = SplitString(strValue,',',m_data_count);
	file.Close();
}

//读取log文件节点配置
void charDataAnalyzer::readNodeConfigFromLogFile(CString path)
{
	CStdioFile file;
	if (!file.Open(path, CFile::modeRead))
	{  
		return;
	}
	CString strValue = "";
	while(file.ReadString(strValue))
	{
		if(getDataType(strValue) == LINE_TYPE_CONFIG)//判断是否为config
		{
			m_nodeConfig = SplitString(strValue,',',m_data_count);
			file.Close();
			return;
		}
	}
	file.Close();
}

//读取期望电流配置
void charDataAnalyzer::readExpectCurrentConfigFromFile()
{
	CStdioFile file;
	if (!file.Open(getFilePath(_T(EXPECT_CONFIG_FILE_PATH)), CFile::modeRead))
	{  
		return;
	}
	CString strValue = "";
	CString* strSplit;
	expectConfig configTemp;
	int iSubStrs;
	while(file.ReadString(strValue))
	{
		strSplit = SplitString(strValue,',',iSubStrs);
		configTemp.mode = atoi(strSplit[0]);
		configTemp.referDataIndex = getNodeIndex(strSplit[1]);
		if(iSubStrs>2)
		{
			configTemp.equalValue = strSplit[2];
		}
		expectConfigArray.push_back(configTemp);
	}
	file.Close();
}

//获得单独预期电流
float charDataAnalyzer::getCurrentExpectSingle(int index)
{
	float result = CURRENT_MAX;
	for(int i = 0; i < (int)expectConfigArray.size(); i++)
	{
		switch(expectConfigArray[i].mode)
		{
		case ECC_LESS_THAN:
			(result > atof(mData[expectConfigArray[i].referDataIndex][index]))?atof(mData[expectConfigArray[i].referDataIndex][index]):result;
			break;
		case ECC_EQUAL:
			{
				int count;
				CString* split = SplitString(expectConfigArray[i].equalValue, '/', count);
				for(int j = 0; j < count; j++)
				{
					if(!mData[expectConfigArray[i].referDataIndex][index].Compare(split[j]))
						return 0;
				}
			}
			break;
		case ECC_GET_LESS:
			break;
		default:
			break;
		}
	}
	return result/MILLI;
}

//根据文件节点名获得index
int charDataAnalyzer::getNodeIndex(CString nodeName){
	for(int i=0; i< m_data_count; i++)
	{
		if(!m_nodeConfig[i].Compare(nodeName))
			return i;
	}
	return -1;
}

int charDataAnalyzer::dataPhoneProcess(){
	char logFilePath[CMD_COMMAND_COUNT_MAX];
	char adbPull[CMD_COMMAND_COUNT_MAX];
	sprintf_s(logFilePath,CMD_COMMAND_COUNT_MAX,"%s/%s",PHONE_LOG_PATH,PHONE_LOG_NAME);
	sprintf_s(adbPull,CMD_COMMAND_COUNT_MAX,"adb pull %s %s",logFilePath,getFilePath(PHONE_LOG_NAME));
	CString cmdResult = sendCMDCommand(adbPull);
	if(!strstr(cmdResult,logFilePath)){
		return 2;
	}
	readNodeConfigFromLogFile(getFilePath(PHONE_LOG_NAME));
	if(dataProcess(getFilePath(PHONE_LOG_NAME))==0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


//分割字符串
CString * SplitString(CString str, char split, int& iSubStrs)  
{  
    int iPos = 0; //分割符位置  
    int iNums = 0; //分割符的总数  
    CString strTemp = str;
    CString strRight;
    //先计算子字符串的数量  
    while (iPos != -1)  
    {  
        iPos = strTemp.Find(split);  
        if (iPos == -1)  
        {  
            break;  
        }  
        strRight = strTemp.Mid(iPos + 1, str.GetLength());  
        strTemp = strRight;  
        iNums++;  
    }  
    if (iNums == 0) //没有找到分割符  
    {  
        //子字符串数就是字符串本身  
        iSubStrs = 1;   
        return NULL;  
    }  
    //子字符串数组  
    iSubStrs = iNums + 1; //子串的数量 = 分割符数量 + 1  
    CString* pStrSplit;  
    pStrSplit = new CString[iSubStrs];  
    strTemp = str;  
    CString strLeft;  
    for (int i = 0; i < iNums; i++)  
    {  
        iPos = strTemp.Find(split);  
        //左子串  
        strLeft = strTemp.Left(iPos);  
        //右子串  
        strRight = strTemp.Mid(iPos + 1, strTemp.GetLength());  
        strTemp = strRight;  
        pStrSplit[i] = strLeft;  
    }  
    pStrSplit[iNums] = strTemp;  
    return pStrSplit;  
}

//获得当前文件路径
CString getFilePath(CString fileName)
{
	TCHAR szPath[MAX_PATH];   
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString PathName(szPath);
	return PathName.Left(PathName.ReverseFind('\\') + 1)+= fileName;
}

CString sendCMDCommand(CString cmd)
{
    SECURITY_ATTRIBUTES sa;  
    HANDLE hRead,hWrite;  
  
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);  
    sa.lpSecurityDescriptor = NULL;  
    sa.bInheritHandle = TRUE;  
  
    if(!CreatePipe(&hRead,&hWrite,&sa,0))  
    {  
        return "";  
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
    stredit2 = cmd;
    tmp.Format("cmd /C %s",stredit2);  
    sprintf_s(cmdline,CMD_COMMAND_COUNT_MAX,"%s",tmp);  
  
    if(!CreateProcess(NULL,cmdline,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))  
    {  
        return "";  
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
        Sleep(200);  
    }  
    CloseHandle(hRead);

	return strOutput;
}