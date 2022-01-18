#pragma once
#include "ParamBase.h"

class VideoCover:public CParamBase
{
public:
	std::string QueryAll(bool bDefault);
	std::string QueryOne(int n);
	void StructToJson(int i);

	int SaveAll(std::string strData);

	std::vector<RSNet_SoleVideoCover_t> m_vec;
};
