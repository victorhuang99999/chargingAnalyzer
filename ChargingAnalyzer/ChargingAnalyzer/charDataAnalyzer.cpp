#include "StdAfx.h"
#include "charDataAnalyzer.h"


charDataAnalyzer::charDataAnalyzer(void)
{
	readNodeConfigFromFile();
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
	CString strValue = _T("");
	CString* strSplit;
	mData.resize(m_data_count);
	int iSubStrs;
	while(file.ReadString(strValue))
	{
		
		if(isData(strValue))//判断是否为数据
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

//判断是否是数据行
bool charDataAnalyzer::isData(CString str){
	if(str.IsEmpty())
		return false;
	if(str[0]>='0' && str[0]<='9')
		return true;
	else
		return false;
}

//获得当前电流进程
std::vector<float> charDataAnalyzer::currentNowProcess()
{
	std::vector<float> nowData;
	for(int i = 0; i < (int)mData[0].size(); i++){
		nowData.push_back((float)_wtof(mData[getNodeIndex(_T(NC_BATTERY_CURRENT_NOW))][i])/(-MILLI));
	}
	return nowData;
}

//获得当前电压进程
std::vector<float> charDataAnalyzer::voltageNowProcess()
{
	std::vector<float> nowData;
	for(int i = 0; i < (int)mData[0].size(); i++){
		nowData.push_back((float)_wtof(mData[getNodeIndex(_T(NC_BATTERY_VOLTAGE_NOW))][i])/MILLI);
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

//读取文件节点配置
void charDataAnalyzer::readNodeConfigFromFile()
{
	CStdioFile file;
	if (!file.Open(getFilePath(_T(NODE_CONFIG_FILE_PATH)), CFile::modeRead))
	{  
		return;
	}
	CString strValue = _T("");
	file.ReadString(strValue);
	m_nodeConfig = SplitString(strValue,',',m_data_count);
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
	CString strValue = _T("");
	CString* strSplit;
	expectConfig configTemp;
	int iSubStrs;
	while(file.ReadString(strValue))
	{
		strSplit = SplitString(strValue,',',iSubStrs);
		configTemp.mode = _wtoi(strSplit[0]);
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
			(result > _wtof(mData[expectConfigArray[i].referDataIndex][index]))?_wtof(mData[expectConfigArray[i].referDataIndex][index]):result;
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
	return PathName.Left(PathName.ReverseFind(_T('\\')) + 1)+= fileName;
}
