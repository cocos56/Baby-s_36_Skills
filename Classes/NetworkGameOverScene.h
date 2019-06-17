#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class NetworkGameOverScene : public Layer, public EditBoxDelegate, public NetworkBaseScene
{
	QE_SINGLETON_H(NetworkGameOverScene);
	QE_CreateSceneFromLayer_H(NetworkGameOverScene);
	NW_BaseScene;
public:
	static void dealServerResponse(int statusCode);
	static int _winFlag;
private:
	//标签相关
	void initLabel();

	//菜单相关
	void initMenu();
	//菜单按钮回调函数相关
	void back();
};