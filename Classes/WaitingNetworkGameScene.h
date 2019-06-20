#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class WaitingNetworkGameScene : public Layer, public EditBoxDelegate, public NetworkBaseScene
{
	QE_SINGLETON_H(WaitingNetworkGameScene);
	QE_CreateSceneFromLayer_H(WaitingNetworkGameScene);
	NW_BaseScene;
public:
	static void dealServerResponse(int statusCode);
private:
	//背景精灵相关
	static vector< Sprite*> _onSprites;
	static Sprite* _sprite;
	void initSprits();
	void setSpriteStatus(int index, bool visible = true);
	void createSprite(int x);

	//发送信息
	void sendMsg();

	//菜单相关
	void initMenu();
	//菜单按钮回调函数相关
	void back();
};