#pragma once
#include "ParamBase.h"

class XinQiaoFD:public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	void StructToJson(int n);
	int SaveAll(std::string strData);

	std::string m_str;

	//RSNet_SoleSiaIntParam_t m_Struct;
	std::vector<RSNet_SoleSiaIntParam_t> m_vec;	
};
