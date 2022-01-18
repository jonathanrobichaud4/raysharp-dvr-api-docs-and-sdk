#pragma once
#include "ParamBase.h"

class SwannCloSto : public CParamBase
{
public:
	std::string QueryAll(bool bDefault);
	void StructToJson(int i);

	int SaveAll(std::string strData);

	RSNet_NewCloudStorage_t m_CloudStorageSet;
	std::vector<RSNet_soleNewCloudStorage_t> m_vec;
	std::string m_str;
};
