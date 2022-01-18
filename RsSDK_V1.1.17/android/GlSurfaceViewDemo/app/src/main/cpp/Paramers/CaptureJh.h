#pragma once
#include "ParamBase.h"

class CaptureJh : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson(int n);
	
	int SaveAll(std::string strData);

	std::vector <RSNet_SoleCapSchedule_t> m_vec;	
};
