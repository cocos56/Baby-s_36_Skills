#pragma execution_character_set("utf-8")

#include "NetworkGameOverScene.h"

string NetworkGameOverScene::_Loser = "babyLose";
//else if (_Loser == "s") { fn = "scoundrelLose"; }
//else if (_Loser == "r") { fn = "refereeLose"; }

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

void NetworkGameOverScene::initSprite(){ addChild(QSprite::createBg(_Loser + ".png")); }

void NetworkGameOverScene::initMenu(){ QE_CreateLabelMenu(10, 500, "返回", NetworkGameOverScene, back); }

void NetworkGameOverScene::back() { QE_ReplaceScene(NetworkGameScene); };