#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class SignInScene : public Layer, public EditBoxDelegate, public NetworkBaseScene
{
	QE_SINGLETON_H(SignInScene);
	QE_CreateSceneFromLayer_H(SignInScene);
	NW_BaseScene;
public:
	static void dealServerResponse(int statusCode);
	static EditBox* _idBox, * _passwordBox;
	static string _nickName;
private:
	//标签相关
	void initLabel();

	//菜单相关
	void initMenu();
	//菜单按钮回调函数相关
	void signIn();
	void signUp();
	void back();

	//输入框相关
	void initEditBox();
};