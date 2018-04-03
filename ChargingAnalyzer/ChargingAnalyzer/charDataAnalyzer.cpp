#include "StdAfx.h"
#include "charDataAnalyzer.h"


charDataAnalyzer::charDataAnalyzer(void)
{
}


charDataAnalyzer::~charDataAnalyzer(void)
{
}

int charDataAnalyzer::dataProcess(CString path)
{
	CStdioFile file;
	if (!file.Open(path, CFile::modeRead))
	{  
		return 1;
	}
	mFileContent.clear();//清空数据
	CString strValue = _T("");
	CString* strSplit;
	int iSubStrs = 0;
	CString temp;
	mData.resize(117);
	while(file.ReadString(strValue))
	{
		
		if(isData(strValue))//判断是否为数据
		{
			strSplit = SplitString(strValue,',');
			for(int i = 0;i < 117; i++ )
			{
				mData[i].push_back(strSplit[i]);
			}
		}
	}
	file.Close();
	return 0;
}

bool charDataAnalyzer::isData(CString str){
	if(str.IsEmpty())
		return false;
	if(str[0]>='0' && str[0]<='9')
		return true;
	else
		return false;
}

//data analyze
void charDataAnalyzer::dataAnalyze(){
	
}

CString * charDataAnalyzer::SplitString(CString str, char split/*, int& iSubStrs*/)  
{  
    int iPos = 0; //分割符位置  
    int iNums = 0; //分割符的总数  
    CString strTemp = str;
    CString strRight;
	int iSubStrs;
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