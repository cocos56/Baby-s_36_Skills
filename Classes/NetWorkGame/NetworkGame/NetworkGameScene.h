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
	//精灵
	static vector< Sprite*> _onSprites;
	static Sprite* _spr, *_confirmSpr, *_judgeSpr;
	void initSprits();
	void createSprite(int x, int y, string identity);
	void setOnSprite(int index);
	void initConfrimSprite();
	Sprite* createSprite(const string& picture);
	void createSprite(int x, const string& picture, const ccMenuCallback& callback);

	//菜单相关
	static Menu* _menu, * _sendMenu;
	void initMenu();
	//菜单按钮回调函数相关
	void send();
	void back();

	//输入框相关
	static EditBox* _msgBox;
	void initEditBox();

	//聊天信息相关
	ListView* _listView;
	void initListView();
	void addListViewElement(const string msg, const string pic);
	void myTurn(bool isMyTurn = false);
	void endChat();
	void yes();
	void no();
	void babyWin();
	void scoundrelWin();
	void goOn();

	//
	virtual void onEnterTransitionDidFinish();
};