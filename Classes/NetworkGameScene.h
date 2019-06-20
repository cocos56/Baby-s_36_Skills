#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class NetworkGameScene : public Layer, public EditBoxDelegate, public NetworkBaseScene
{
	QE_SINGLETON_H(NetworkGameScene);
	QE_CreateSceneFromLayer_H(NetworkGameScene);
	NW_BaseScene;
public:
	static void dealServerResponse(int statusCode);
private:
	//背景精灵
	static vector< Sprite*> _onSprites;
	static Sprite* _spr;
	void initSprits();
	void createSprite(int x, int y, string identity);
	void setOnSprites(int index);

	//标签相关
	void initLabel();

	//菜单相关
	void initMenu();
	//菜单按钮回调函数相关
	void send();
	void back();

	//输入框相关
	static EditBox* _nameBox, * _passwordBox;
	void initEditBox();

	//聊天信息相关
	ListView* _listView;
	void initListView();
	void addListViewElement(const string msg, const string pic);
	void initLayer();
	void confirm();
};