#pragma once
#include <vector>
#include "charAnaConfig.h"
class charDataAnalyzer
{
public:
	charDataAnalyzer(void);
	~charDataAnalyzer(void);

	int dataProcess(CString path);
	float* getCurrentExpect();

	std::vector<CString> mFileContent;
	std::vector<std::vector<CString>> mData;

private:
	void dataAnalyze();
	bool isData(CString);
	CString * SplitString(CString str, char split);
};

