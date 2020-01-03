#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class LogoScene :public Layer
{
public:
    static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(LogoScene);
	void startScene();
};

