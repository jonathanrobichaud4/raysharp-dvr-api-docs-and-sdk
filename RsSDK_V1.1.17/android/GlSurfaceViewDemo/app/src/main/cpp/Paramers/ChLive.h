#pragma once
#include "ParamBase.h"

class ChLive : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	std::string QueryOne(int n);
	void StructToJson(int n);

	int SaveAll(std::string strData);

	std::vector<RSNetNew_SoleLivingset_t> m_vec;
	std::string m_str;
};
