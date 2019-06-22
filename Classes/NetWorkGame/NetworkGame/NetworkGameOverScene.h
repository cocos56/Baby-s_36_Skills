#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class NetworkGameOverScene : public Layer
{
	QE_SINGLETON_H(NetworkGameOverScene);
	QE_CreateSceneFromLayer_H(NetworkGameOverScene);
public:
	static string _Loser;
private:
	//精灵相关
	void initSprite();

	//菜单相关
	void initMenu();
	//菜单按钮回调函数相关
	void back();
};