#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class SignInSceneTest : public Layer, public EditBoxDelegate, public NetworkBaseScene
{
	QE_CreateSceneFromLayer_H(SignInSceneTest);
	NW_BaseScene;
public:
	//服务器状态相关
	static EditBox* _idBox, * _passwordBox;

private:
	void initLabel() {};

	//菜单相关
	void initMenu();
	//菜单按钮回调函数相关
	void SignIn();
	void SignUp();

	//输入框相关
	void initEditBox();
};