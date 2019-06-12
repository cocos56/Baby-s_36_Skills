#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class SignUpScene : public Layer, public EditBoxDelegate, public NetworkBaseScene
{
	QE_CreateSceneFromLayer_H(SignUpScene);
	NW_BaseScene;
public:
private:
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