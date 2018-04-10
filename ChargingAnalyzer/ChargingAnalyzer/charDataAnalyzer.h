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

#define PHONE_LOG_PATH "data/vendor/bslogs/battery"
#define PHONE_LOG_NAME "Battery_Daemon_info.csv"
#define CMD_COMMAND_COUNT_MAX 200

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

enum{
	LINE_TYPE_NONE = 0,
	LINE_TYPE_DATA = 1,
	LINE_TYPE_CONFIG = 2,
};

CString * SplitString(CString str, char split,int& iSubStrs);//分割源数据
CString getFilePath(CString fileName);
CString sendCMDCommand(CString cmd);//发送cmd命令

class charDataAnalyzer
{
public:
	charDataAnalyzer(void);
	~charDataAnalyzer(void);

	int dataProcess(CString path);//数据处理进程
	int dataPhoneProcess();
	
	std::vector<std::vector<CString>> mData;
	std::vector<float> mCurrentNowData;
	std::vector<float> mCurrentExpectData;
	std::vector<float> mVoltageNowData;

private:
	//配置相关
	CString* m_nodeConfig;//文件节点配置
	int m_data_count;//文件节点数量
	int getNodeIndex(CString nodeName);//获得文件节点index

	std::vector<expectConfig> expectConfigArray;//期望电流配置数组
	float getCurrentExpectSingle(int index);//获得单个期望电流

	std::vector<float> currentNowProcess();//电流数据进程
	std::vector<float> voltageNowProcess();//电压数据进程
	std::vector<float> currentExpectProcess();//期望电流数据进程

	void clearData();//清空数据
	int getDataType(CString);//判断是否是数据

	void readNodeConfigFromConfigFile();
	void readNodeConfigFromLogFile(CString path);
	void readExpectCurrentConfigFromFile();
};