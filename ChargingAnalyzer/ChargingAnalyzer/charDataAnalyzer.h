#pragma once
#include <vector>

#define NODE_CONFIG_FILE_PATH "config/nodeConfig.csv"
#define EXPECT_CONFIG_FILE_PATH "config/expectConfig.csv"

#define MILLI 1000000
#define CURRENT_MAX 4*MILLI

#define NC_USB_ONLINE "usb_online"
#define NC_USB_PRESENT "usb_present"
#define NC_USB_REAL_TYPE "usb_real_type"
#define NC_USB_INPUT_CURRENT_SETTLED "usb_input_current_settled"
#define NC_USB_CURRENT_NOW "usb_current_now"
#define NC_BATTERY_CHARGE_DONE "battery_charge_done"
#define NC_BATTERY_THERMAL_CHARGE_CURRENT_MAX "battery_thermal_charge_current_max"
#define NC_BATTERY_VOLTAGE_NOW "battery_voltage_now"
#define NC_BATTERY_TEMP "battery_temp"
#define NC_BATTERY_CURRENT_NOW "battery_current_now"
#define NC_BATTERY_CHARGER_TEMP "battery_charger_temp"
#define NC_BATTERY_CHARGE_TYPE "battery_charge_type"

struct expectConfig{
	int mode;
	int referDataIndex;
	CString equalValue;
};

enum{
	ECC_LESS_THAN = 1,
	ECC_EQUAL = 2,
	ECC_GET_LESS = 3,
};

CString * SplitString(CString str, char split,int& iSubStrs);//�ָ�Դ����
CString getFilePath(CString fileName);

class charDataAnalyzer
{
public:
	charDataAnalyzer(void);
	~charDataAnalyzer(void);

	int dataProcess(CString path);//���ݴ������
	
	std::vector<std::vector<CString>> mData;
	std::vector<float> mCurrentNowData;
	std::vector<float> mCurrentExpectData;
	std::vector<float> mVoltageNowData;

private:
	//�������
	CString* m_nodeConfig;//�ļ��ڵ�����
	int m_data_count;//�ļ��ڵ�����
	int getNodeIndex(CString nodeName);//����ļ��ڵ�index

	std::vector<expectConfig> expectConfigArray;//����������������
	float getCurrentExpectSingle(int index);//��õ�����������

	std::vector<float> currentNowProcess();//�������ݽ���
	std::vector<float> voltageNowProcess();//��ѹ���ݽ���
	std::vector<float> currentExpectProcess();//�����������ݽ���

	void clearData();//�������
	bool isData(CString);//�ж��Ƿ�������

	void readNodeConfigFromFile();
	void readExpectCurrentConfigFromFile();
};