#pragma once
#include "ParamBase.h"

class AlarmIO: public CParamBase
{
public:
	AlarmIO(void);

	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);

	int SaveAll(std::string strData);

	std::vector< RSNet_SoleIOAlarmSet_t> m_vec;
	int AlarmOutNum;
};
