#pragma once
#include "ParamBase.h"

class LiveParam:public CParamBase
{
public:
	std::string QueryOne(int n);
    std::string QueryAll(std::string strData);

    void StructToJson(int i);
	int SaveOne(int n,std::string strData);

	RSNet_SolePreviewCtrl_t m_Struct;
    std::vector < RSNet_SolePreviewCtrl_t> m_vec;
};
