#pragma once
#include "ParamBase.h"

class RSPushSubscription :public CParamBase
{
public:
    RSPushSubscription(void);
    ~RSPushSubscription(void);
    
public:
    virtual int SaveAll(std::string strData);
    virtual std::string QueryAll(bool bDefault = false);
private:
    
};
