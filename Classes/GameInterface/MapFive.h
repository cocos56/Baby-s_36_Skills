#pragma execution_character_set("utf-8")
#pragma once
#include "cocos2d.h"
USING_NS_CC;
class MapFive :public Layer
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(MapFive);
	void backTwo();
private:
	Sprite* hero;
	bool HeroDirecton;
};
class HrockerLayer5:public Layer
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(HrockerLayer5);

};

