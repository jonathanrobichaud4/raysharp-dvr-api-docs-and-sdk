#pragma once
#include "ParamBase.h"

class IntelligentNewUser : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson(int n);

	int SaveAll(std::string strData);
	std::string m_str;
	std::vector <RSNet_SoleHGIntParam_t> m_vec;
};
