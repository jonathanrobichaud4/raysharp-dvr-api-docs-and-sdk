#pragma once
#include "ParamBase.h"

class GB28181 : public CParamBase
{
public:
	std::string QueryAll(bool bDefault);
	void StructToJson();
	
	int SaveAll(std::string strData);

	std::string m_str;
	RSNet_GB28181Param_t m_Gb28181;
};
