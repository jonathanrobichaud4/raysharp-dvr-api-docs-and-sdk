#pragma once
#include "ParamBase.h"

class VideoRoi : public CParamBase
{
public:
	VideoRoi(void);
	~VideoRoi(void);

	std::string QueryAll(bool bDefault);
	int SaveAll(std::string strData);
	std::vector<RSNet_SoleRoiParam_t> m_vec;
};
