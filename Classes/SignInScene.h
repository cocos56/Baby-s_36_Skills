#pragma once

#include "QE.h"

class SignInScene : public Layer
	, public EditBoxDelegate
{
	QE_CreateSceneFromLayer_H(SignInScene);
public:
	//服务器状态相关
	static void updateLabel();
	static MenuItemLabel* connectItem;
	static LabelTTF* label, * logLabel;
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
	virtual void editBoxEditingDidBegin(EditBox* editBox);
	virtual void editBoxTextChanged(EditBox* editBox, const string& text);
	virtual void editBoxEditingDidEnd(EditBox* editBox);
	virtual void editBoxReturn(EditBox* editBox);
};