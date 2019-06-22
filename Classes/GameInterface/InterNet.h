#pragma execution_character_set("utf-8")
#pragma once
#include "cocos2d.h"
USING_NS_CC;
class InterNet :public Layer
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(InterNet);	
};

