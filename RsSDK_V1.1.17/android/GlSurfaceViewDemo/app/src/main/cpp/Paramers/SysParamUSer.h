#pragma once
#include "ParamBase.h"

class SysParamUSer : public CParamBase
{
public:
	SysParamUSer()
	{
		m_nClient = -1;
	}
	std::string QueryAll(bool bDefault = false);
	std::string QueryAll(std::string strData);
	int m_nClient;
	void StructToJson(int i);

	int SaveAll(std::string strData);
	std::string m_str;

	RSNet_UserSet_t m_UserSet;
	std::vector<RSNet_SoleUserInfo_t> m_vec;	

	int ModifyPassword(std::string staData);
};
