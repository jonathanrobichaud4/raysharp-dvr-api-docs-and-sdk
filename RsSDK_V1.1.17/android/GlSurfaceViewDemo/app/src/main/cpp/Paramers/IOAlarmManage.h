#pragma once
#include "ParamBase.h"

class IOAlarmManage :public CParamBase
{
public:
	IOAlarmManage(void);
	~IOAlarmManage(void);
public:
	std::string QueryAll(bool bDefault = false);

	int SaveAll(std::string strData);

	RSNet_IoAlarmManage_t m_IoAlarmManage;
};
