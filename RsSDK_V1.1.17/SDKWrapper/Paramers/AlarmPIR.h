#pragma once
#include "ParamBase.h"

class AlarmPIR : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	std::string QueryOne(int n);

	void StructToJson(int n);
	//void DataToCover_One(int i);
	int AlarmOutNum;

	int SaveAll(std::string strData);

	AlarmPIR(void);

	std::vector<RSNet_SolePirMotionSet_t> m_vec;	
};
