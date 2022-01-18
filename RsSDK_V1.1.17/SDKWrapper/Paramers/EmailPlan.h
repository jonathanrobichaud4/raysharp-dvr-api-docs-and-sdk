#pragma once
#include "ParamBase.h"

class EmailPlan :	public CParamBase
{
public:
	std::string QueryAll(bool bDefault = false);
	void StructToJson(int n);

	int SaveAll(std::string strData);

	RSNetNew_EmailScheduleset_t m_Email;
	std::vector <RSNetNew_SoleEmailScheduleset_t> m_vec;	
};
