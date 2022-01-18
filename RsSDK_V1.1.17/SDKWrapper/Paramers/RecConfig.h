#pragma once
#include "ParamBase.h"

class RecConfig : public CParamBase
{
public:
	std::string QueryAll(bool bDefault);
	void StructToJson(int i);

	int SaveAll(std::string strData);

	RSNet_RecordSet_t m_RecordSet;
	std::vector<RSNet_SoleRecordSet_t> m_vec;
};
