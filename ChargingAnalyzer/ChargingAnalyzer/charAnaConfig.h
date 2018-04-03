#pragma once
#include <vector>

class charAnaConfig
{
public:
	charAnaConfig(void);
	~charAnaConfig(void);

	//config class
	void loadConfig();
	CString DEFAULT_CONFIG_PATH;
	int getIDByNodeName(CString name);

	std::vector<CString> nodeName;
};

