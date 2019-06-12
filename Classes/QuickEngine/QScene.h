#pragma execution_character_set("utf-8")
#pragma once

/*
Quick Engine所属快速场景模块
含：
1.QScene类
用途：用于快速管理场景
*/

#include "cocos2d.h"
USING_NS_CC;
#include "QDesignMode.h"

#define QE_ReplaceScene(__TYPE__) Director::getInstance()->replaceScene(__TYPE__::createScene());

#define QE_winSize Size(960, 540);
#define QE_get_winSize Size winSize = QE_winSize;

#define QE_CreateSceneFromLayer_CPP(TYPE) \
Scene* TYPE::createScene() \
{ \
	Scene* scene = Scene::create(); \
	Layer* layer = TYPE::create(); \
	scene->addChild(layer); \
	return scene; \
} \
 \
bool TYPE::init() \
{ \
	if (!Layer::init()) \
	{ \
		return false; \
	} \
vector<string> paths;

#define QE_CreateSceneFromLayer_H(TYPE) \
public: \
static Scene* createScene(); \
virtual bool init(); \
CREATE_FUNC(TYPE); \
QE_get_winSize

class QScene
{
public:
	//will save now scene to pause.png
	static void saveNowSceneToFile();
};