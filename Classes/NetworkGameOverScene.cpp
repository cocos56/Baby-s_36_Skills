#pragma execution_character_set("utf-8")

#include "NetworkGameOverScene.h"


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
	createLabel("坏人：");
	_label->setPosition(60, 390);
	createLabel("宝宝：");
	_label->setPosition(60, 325);
	createLabel("裁判：");
	_label->setPosition(60, 265);

	NW_InitLogLabel(150, 20);
}

void NetworkGameOverScene::initMenu()
{
	QE_CreateLabelMenu(840, 100, "发送", NetworkGameOverScene, createRoom);
	QE_CreateLabelMenuAgain(10, 500, "返回", NetworkGameOverScene, back);
}

void NetworkGameOverScene::createRoom()
{

}

void NetworkGameOverScene::joinRoom()
{

}

void NetworkGameOverScene::back() { QE_ReplaceScene(SignInScene); };