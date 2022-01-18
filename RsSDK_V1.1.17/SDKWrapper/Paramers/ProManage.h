#pragma once
#include "ParamBase.h"

class ProManage : public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);

	int SaveAll(std::string strData);

	std::vector <RSNetNew_SoleCustomProtocol_t> m_vec;
	std::string m_str;
};
