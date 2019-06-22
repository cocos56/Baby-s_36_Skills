#pragma execution_character_set("utf-8")

#include "NetworkGameOverScene.h"

char NetworkGameOverScene::_Loser = 'b';

QE_SINGLETON2_CPP(NetworkGameOverScene);

QE_CreateSceneFromLayer_CPP(NetworkGameOverScene);
	paths = { "fonts", "NetworkGameOverScene" };
	QE_SetResourcesSearchDir;

	_instance = this;
	initSprite();
	initMenu();
	return true;
}

void NetworkGameOverScene::dealServerResponse(int statusCode){
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
}

void NetworkGameOverScene::initSprite()
{
	string str;
	if (_Loser == 'b') { str = "babyWin"; }
	else if(_Loser == 's') { str = "坏人玩家：胜"; }
	else if (_Loser == 'r') { str = "裁判断线：平局"; }
	createLabel(str);
	_label->setPosition(400, 325);
	addChild(QSprite::createBg("babyWin.png"));
}

void NetworkGameOverScene::initMenu()
{
	QE_CreateLabelMenu(10, 500, "返回", NetworkGameOverScene, back);
}

void NetworkGameOverScene::back() { QE_ReplaceScene(NetworkGameScene); };