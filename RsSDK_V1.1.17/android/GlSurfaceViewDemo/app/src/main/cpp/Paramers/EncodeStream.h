#pragma once
#include "ParamBase.h"

class MainEncode:public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson(int i);

	int SaveAll(std::string strData);

	std::vector < RSNetNew_SoleStreamset_t> m_vec;
};

class AlarmEncode:public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson(int i);

	int SaveAll(std::string strData);

	std::vector < RSNetNew_SoleStreamset_t> m_vec;
	std::vector < RSNetNew_SoleStreamset_t> m_alarmvec;
};


class SubEncode:public CParamBase
{
public:
	std::string QueryAll(bool isDefault = false);
	void StructToJson(int i);

	int SaveAll(std::string strData);

	std::vector < RSNetNew_SoleStreamset_t> m_vec;
};

class MobileEncode:public CParamBase
{
public:
	MobileEncode(void);

	std::string QueryAll(bool isDefault = false);
		void StructToJson(int i);
		void StructToJson_Area(int i);
	
	int SaveAll(std::string strData);

	std::vector < RSNetNew_SoleStreamset_t> m_vec;

	std::vector < RSNetNew_AreaStreamset_t> m_vecArea;
	int nArea;
};

