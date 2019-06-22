#pragma execution_character_set("utf-8")

#include "NetworkGameOverScene.h"

string NetworkGameOverScene::_Loser = "refereeLose";

QE_SINGLETON2_CPP(NetworkGameOverScene);

QE_CreateSceneFromLayer_CPP(NetworkGameOverScene);
	paths = { "fonts", "NetworkGameOverScene" };
	QE_SetResourcesSearchDir;

	_instance = this;
	initSprite();
	initMenu();
	return true;
}

void NetworkGameOverScene::initSprite(){ addChild(QSprite::createBg(_Loser + ".png")); }

void NetworkGameOverScene::initMenu(){ QE_CreateLabelMenu(10, 500, "返回", NetworkGameOverScene, back); }

void NetworkGameOverScene::back() { QE_ReplaceScene(NetworkGameScene); };