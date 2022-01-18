#pragma once
#include "ParamBase.h"

class GoodsLostLegacy : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson(int n);

	int SaveAll(std::string strData);
	
	std::vector <RSNet_SoleGoodsLostLegacy_t> m_vec;
};
