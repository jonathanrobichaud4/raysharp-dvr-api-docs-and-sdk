#pragma once
#include "ParamBase.h"

class RTSP : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);

	int SaveAll(std::string strData);

	std::string m_str;

	RSNet_Rtsp_t m_Rtsp;


};
