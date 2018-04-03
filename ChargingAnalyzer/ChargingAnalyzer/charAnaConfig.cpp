#include "StdAfx.h"
#include "charAnaConfig.h"


charAnaConfig::charAnaConfig(void)
{
	loadConfig();
}


charAnaConfig::~charAnaConfig(void)
{
}

void charAnaConfig::loadConfig()
{
	for(int i = 0; i<117;i++)
	{
		nodeName.push_back(L"");
	}
	nodeName[113] = "battery_current_now";
}

int charAnaConfig::getIDByNodeName(CString name)
{
	for(int i = 0; i<117;i++){
		if(name.Compare(nodeName[i])==0)
		{
			return i;
		}
	}
	return -1;
}