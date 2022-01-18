#pragma once
#include "ParamBase.h"

class AlarmMotion : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	std::string QueryOne(int n);

	void StructToJson(int n);
	//void DataToCover_One(int i);
	int AlarmOutNum;

	int SaveAll(std::string strData);

	AlarmMotion(void);

	std::vector<RSNet_SoleMotionSet_t> m_vec;	
	//RSNet_SoleVideoCover_t m_cover[MAX_CHANNEL];
};
