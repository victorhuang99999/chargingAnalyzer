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

//�������ݽ���
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
		
		if(isData(strValue))//�ж��Ƿ�Ϊ����
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

//�������
void charDataAnalyzer::clearData()
{
	mData.clear();
	mCurrentNowData.clear();
	mCurrentExpectData.clear();
	mVoltageNowData.clear();
}

//�ж��Ƿ���������
bool charDataAnalyzer::isData(CString str){
	if(str.IsEmpty())
		return false;
	if(str[0]>='0' && str[0]<='9')
		return true;
	else
		return false;
}

//��õ�ǰ��������
std::vector<float> charDataAnalyzer::currentNowProcess()
{
	std::vector<float> nowData;
	for(int i = 0; i < (int)mData[0].size(); i++){
		nowData.push_back((float)_wtof(mData[getNodeIndex(_T(NC_BATTERY_CURRENT_NOW))][i])/(-MILLI));
	}
	return nowData;
}

//��õ�ǰ��ѹ����
std::vector<float> charDataAnalyzer::voltageNowProcess()
{
	std::vector<float> nowData;
	for(int i = 0; i < (int)mData[0].size(); i++){
		nowData.push_back((float)_wtof(mData[getNodeIndex(_T(NC_BATTERY_VOLTAGE_NOW))][i])/MILLI);
	}
	return nowData;
}

//���Ԥ�ڵ�������
std::vector<float> charDataAnalyzer::currentExpectProcess()
{
	std::vector<float> expectData;
	for(int i = 0; i < (int)mData[0].size(); i++){
		expectData.push_back(getCurrentExpectSingle(i));
	}
	return expectData;
}

//��ȡ�ļ��ڵ�����
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

//��ȡ������������
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

//��õ���Ԥ�ڵ���
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

//�����ļ��ڵ������index
int charDataAnalyzer::getNodeIndex(CString nodeName){
	for(int i=0; i< m_data_count; i++)
	{
		if(!m_nodeConfig[i].Compare(nodeName))
			return i;
	}
	return -1;
}

//�ָ��ַ���
CString * SplitString(CString str, char split, int& iSubStrs)  
{  
    int iPos = 0; //�ָ��λ��  
    int iNums = 0; //�ָ��������  
    CString strTemp = str;
    CString strRight;
    //�ȼ������ַ���������  
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
    if (iNums == 0) //û���ҵ��ָ��  
    {  
        //���ַ����������ַ�������  
        iSubStrs = 1;   
        return NULL;  
    }  
    //���ַ�������  
    iSubStrs = iNums + 1; //�Ӵ������� = �ָ������ + 1  
    CString* pStrSplit;  
    pStrSplit = new CString[iSubStrs];  
    strTemp = str;  
    CString strLeft;  
    for (int i = 0; i < iNums; i++)  
    {  
        iPos = strTemp.Find(split);  
        //���Ӵ�  
        strLeft = strTemp.Left(iPos);  
        //���Ӵ�  
        strRight = strTemp.Mid(iPos + 1, strTemp.GetLength());  
        strTemp = strRight;  
        pStrSplit[i] = strLeft;  
    }  
    pStrSplit[iNums] = strTemp;  
    return pStrSplit;  
}

//��õ�ǰ�ļ�·��
CString getFilePath(CString fileName)
{
	TCHAR szPath[MAX_PATH];   
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString PathName(szPath);
	return PathName.Left(PathName.ReverseFind(_T('\\')) + 1)+= fileName;
}
