#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class SignUpScene : public Layer, public EditBoxDelegate, public NetworkBaseScene
{
	QE_CreateSceneFromLayer_H(SignUpScene);
	NW_BaseScene;
public:
private:
	static EditBox* _unBox, * _nickNameBox, * _passwordBox;
	
	//菜单相关
	void initMenu();

	//菜单按钮回调函数相关
	void SignUp();

	//输入框相关
	void initEditBox();
};