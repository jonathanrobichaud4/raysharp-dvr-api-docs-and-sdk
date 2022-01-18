#pragma once
#include "ParamBase.h"

class ShowIntell:public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);
	std::vector< RSNet_SoleIntManage_t> m_vec;
};
