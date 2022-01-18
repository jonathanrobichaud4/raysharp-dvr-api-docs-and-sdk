#pragma once
#include "ParamBase.h"

class SysParamPTZ : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	std::string QueryOne(int n);
	void StructToJson(int n);

	int SaveAll(std::string strData);
	int SaveOne(int n,std::string strData);

	std::vector <RSNet_SolePTZSet_t> m_vec;
	RSNet_SolePTZSet_t m_Struct;
};
