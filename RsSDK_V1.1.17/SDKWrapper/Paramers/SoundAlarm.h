#pragma once
#include "ParamBase.h"

class SoundAlarm: public CParamBase
{
public:
	SoundAlarm(void);

	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);

	int AlarmOutNum;
	int SaveAll(std::string strData);

	std::vector< RSNet_SoleSoundDetectionParam_t> m_vec;
};
