#pragma execution_character_set("utf-8")
#pragma once
#include "cocos2d.h"
#include<iostream>
USING_NS_CC;
class star :public Layer
{
public:
    static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(star);
	void startScene();
};

