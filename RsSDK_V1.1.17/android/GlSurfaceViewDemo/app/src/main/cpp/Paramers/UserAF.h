#pragma once
#include "ParamBase.h"

class UserAF:public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);
	int SaveAll(std::string strData);
	std::string QueryOne(int n);
	int SaveOne(int n,std::string strData);

	std::vector< RSNet_IPCAutoFocusInfo_t> m_vec;
	RSNet_IPCAutoFocusInfo_t m_Struct;
};