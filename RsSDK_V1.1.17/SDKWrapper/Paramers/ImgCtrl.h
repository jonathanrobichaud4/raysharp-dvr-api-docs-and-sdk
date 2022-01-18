#pragma once
#include "ParamBase.h"

class ImgCtrl : public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	std::string QueryOne(int n);
	void StructToJson(int i);
	std::string QueryAll(std::string strData);
	void CamModeStructToJson(int i);

	int SaveAll(std::string strData);

	std::vector< RSNetNew_CameraSet_t> m_vec;

	std::vector< RSNetNew_CameraModeSet_t> m_vecMode;
};
