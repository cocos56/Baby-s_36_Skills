#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class SelectRoomsScene : public Layer, public EditBoxDelegate, public NetworkBaseScene
{
	QE_SINGLETON_H(SelectRoomsScene);
	QE_CreateSceneFromLayer_H(SelectRoomsScene);
	NW_BaseScene;
public:
	static void dealServerResponse(int statusCode);
	static void dealServerResponse(string str) { NetworkBaseScene::dealServerResponse(str); };
private:
	void enterSignInScene(float f);
	//标签相关
	void initLabel();

	//菜单相关
	void initMenu();
	//菜单按钮回调函数相关
	void signUp();
	void back();

	//输入框相关
	static EditBox* _unBox, * _nickNameBox, * _passwordBox;
	void initEditBox();
};