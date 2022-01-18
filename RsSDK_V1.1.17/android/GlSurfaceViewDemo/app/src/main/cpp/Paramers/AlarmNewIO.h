#pragma once
#include "ParamBase.h"

class AlarmNewIO: public CParamBase
{
public:

	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);

	int SaveAll(std::string strData);

	std::vector< RSNet_NewSoleIOAlarmSet_t> m_vec;
};
