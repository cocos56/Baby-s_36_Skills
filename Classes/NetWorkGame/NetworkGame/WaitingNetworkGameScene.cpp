#pragma execution_character_set("utf-8")

#include "WaitingNetworkGameScene.h"

Sprite* WaitingNetworkGameScene::_sprite;
vector< Sprite*> WaitingNetworkGameScene::_onSprites;

QE_SINGLETON2_CPP(WaitingNetworkGameScene);

QE_CreateSceneFromLayer_CPP(WaitingNetworkGameScene);
	paths = { "fonts", "WaitingNetworkGameScene" };
	QE_SetResourcesSearchDir;

	_instance = this;

	Connect::connect(Connect::Event::Waiting);

	initSprits();
	initMenu();
	return true;
}

void WaitingNetworkGameScene::dealServerResponse(int statusCode)
{
	if (Connect::_nowEvent == 9) { return; }
	if (statusCode == 820) { setSpriteStatus(0, false); }
	else if (statusCode == 821) { setSpriteStatus(0, true); }
	else if (statusCode == 830) { setSpriteStatus(1, false); }
	else if (statusCode == 831) { setSpriteStatus(1, true); }
	else if (statusCode == 840) { setSpriteStatus(2, false); }
	else if (statusCode == 841) { setSpriteStatus(2, true); }
}

void WaitingNetworkGameScene::setSpriteStatus(int index, bool visible) {
	_onSprites[index]->setVisible(visible);
	if (_onSprites[0]->isVisible() && _onSprites[1]->isVisible() && _onSprites[2]->isVisible()){ QE_ReplaceScene(NetworkGameScene); }
	//if (_onSprites[0]->isVisible() || _onSprites[1]->isVisible() || _onSprites[2]->isVisible()) { QE_ReplaceScene(NetworkGameScene); }
}

void WaitingNetworkGameScene::createSprite(int x)
{
	_sprite = QSprite::create("notReady.png", x, 50);
	addChild(_sprite);
	_sprite = QSprite::create("ready.png", x, 50);
	addChild(_sprite);
	_sprite->setVisible(false);
	_onSprites.push_back(_sprite);
}

void WaitingNetworkGameScene::sendMsg()
{
	Connect::createMsg();
	Connect::sendMsg();
}

void WaitingNetworkGameScene::initSprits()
{
	sendMsg();
	if (_onSprites.size() > 0) { _onSprites.clear(); }
	QE_addBgSprite;
	createSprite(90);
	createSprite(680);
	createSprite(385);
}

void WaitingNetworkGameScene::initMenu()
{
	QE_CreateSpriteMenu(40, 520, "back.png", WaitingNetworkGameScene, back);
}

void WaitingNetworkGameScene::back() {
	Connect::createMsg();
	Connect::addMsg("quit", "");
	Connect::sendMsg();
	QE_ReplaceScene(JoinRoomScene);
};