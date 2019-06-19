#pragma execution_character_set("utf-8")

#include "WaitingNetworkGameScene.h"

Sprite* WaitingNetworkGameScene::_sprite;

QE_SINGLETON2_CPP(WaitingNetworkGameScene);

QE_CreateSceneFromLayer_CPP(WaitingNetworkGameScene);
	paths = { "fonts", "WaitingNetworkGameScene" };
	QE_SetResourcesSearchDir;


	_instance = this;

	Connect::connect(Connect::Event::SelectRole);

	initSprits();
	initMenu();
	return true;
}

void WaitingNetworkGameScene::dealServerResponse(int statusCode)
{

}

void WaitingNetworkGameScene::initSprits()
{
	QE_addBgSprite;
	_sprite = QSprite::create("ready.png", 90, 50);
	addChild(_sprite);
	_sprite = QSprite::create("ready.png", 385, 50);
	addChild(_sprite);
	_sprite = QSprite::create("ready.png", 680, 50);
	addChild(_sprite);
	_sprite = QSprite::create("notReady.png", 90, 50);
	//addChild(_sprite);
	_sprite = QSprite::create("notReady.png", 385, 50);
	addChild(_sprite);
	_sprite = QSprite::create("notReady.png", 680, 50);
	//addChild(_sprite);
}

void WaitingNetworkGameScene::initMenu()
{
	QE_CreateLabelMenu(10, 500, "返回", WaitingNetworkGameScene, back);
}

void WaitingNetworkGameScene::back() { QE_ReplaceScene(JoinRoomScene); };