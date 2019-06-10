#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class SignInScene : public Layer, public EditBoxDelegate
{
	QE_CreateSceneFromLayer_H(SignInScene);
public:
	//服务器状态相关
	static Label* _label, * _logLabel;
	static EditBox* _idBox, * _passwordBox;
	//处理服务器相应的数据
	static void dealServerResponse();
	static void dealServerResponse(string str);
private:
	void createLabel(string show);
	//菜单相关
	void initMenu();
	//菜单按钮回调函数相关
	void SignIn();
	void SignUp();

	//输入框相关
	void initEditBox();
	EditBox* createEditBox(string normalPngFile);
	virtual void editBoxReturn(EditBox* editBox) {};
};