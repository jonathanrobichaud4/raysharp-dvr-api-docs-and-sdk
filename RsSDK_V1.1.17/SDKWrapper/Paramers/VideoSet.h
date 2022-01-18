#pragma once
#include "ParamBase.h"

class VideoSet:public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	std::string QueryOne(int n);

	void StructToJson(int n);

	int SaveOne(int n, std::string strData);
	int SaveAll(std::string strData);

	RSNet_SoleColorSet_t m_Struct;
	std::vector<RSNet_SoleColorSet_t> m_vec;
};
