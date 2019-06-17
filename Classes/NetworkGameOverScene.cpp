#pragma execution_character_set("utf-8")

#include "NetworkGameOverScene.h"

int NetworkGameOverScene::_winFlag = 1;

QE_SINGLETON2_CPP(NetworkGameOverScene);

QE_CreateSceneFromLayer_CPP(NetworkGameOverScene);
	paths = { "fonts", "icon" };
	QE_SetResourcesSearchDir;

	_instance = this;

	Connect::connect(Connect::Event::Dialog);

	initLabel();
	initMenu();
	return true;
}

void NetworkGameOverScene::dealServerResponse(int statusCode)
{
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
}

void NetworkGameOverScene::initLabel()
{
	createLabel("本局结果");
	_label->setPosition(430, 390);
	string str;
	if (_winFlag == 1) { str = "宝宝玩家：胜"; }
	else if(_winFlag == 2) { str = "坏人玩家：胜"; }
	else if (_winFlag == 3) { str = "裁判断线：平局"; }
	createLabel(str);
	_label->setPosition(400, 325);
}

void NetworkGameOverScene::initMenu()
{
	QE_CreateLabelMenu(10, 500, "返回", NetworkGameOverScene, back);
}

void NetworkGameOverScene::back() { QE_ReplaceScene(SignInScene); };