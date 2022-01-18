#pragma once
#include "ParamBase.h"

class AlarmPtz : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson(int i);

	int SaveAll(std::string strData);

	std::vector<RSNet_SoleAlarmLinkagePtz_t> m_vec;
	RSNet_AlarmLinkagePtz_t m_ptz;
};