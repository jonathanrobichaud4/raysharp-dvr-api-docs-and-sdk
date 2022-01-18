#pragma once
#include "ParamBase.h"

class FaceDetection : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	std::string QueryAll(std::string strData);
	void StructToJson(int n);

	int SaveAll(std::string strData);
	
	std::vector <RSNet_SoleIntHumanFace_t> m_vec;
};
