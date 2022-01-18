#pragma once
#include "ParamBase.h"

class IPFilter : public CParamBase
{
public:
	IPFilter(void);
	~IPFilter(void);

	std::string QueryAll(std::string strData);
	std::string QueryAll(bool bDefault);
	int SaveAll(std::string strData);

	RSNet_IPFilter_t m_Filter;
	std::vector<RSNet_SoleIPFilter_t> m_vec;
};
