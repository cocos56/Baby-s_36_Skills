#pragma execution_character_set("utf-8")

#include "SignInScene.h"

EditBox* SignInScene::_idBox, * SignInScene::_passwordBox;

QE_CreateSceneFromLayer_CPP(SignInScene);
	paths = { "fonts" };
	QE_SetResourcesSearchDir;

	Connect::connect(Connect::Event::SignIn);

	initLabel();
	initMenu();
	initEditBox();
	return true;
}

void SignInScene::initLabel()
{
	string str;
	if (Connect::_ws) { str = ConnectStatus(SignInCase1Successful); }
	else { str = ConnectStatus(SignInCase1Failed); }
	_logLabel = createLabel(str);
	_logLabel->setPosition(150, 150);
}

void SignInScene::initMenu()
{
	QE_CreateLabelMenu(380, 270, "登录", SignInScene, signIn);
	QE_CreateLabelMenuAgain(530, 270, "注册", SignInScene, signUp);
	QE_CreateLabelMenuAgain(10, 500, "返回", SignInScene, back);
}

void SignInScene::signIn()
{

}

void SignInScene::signUp() { QE_ReplaceScene(SignUpScene); };

void SignInScene::back() { QE_ReplaceScene(ConnectServerScene); };

void SignInScene::initEditBox()
{
	//输入ID的框
	_box = createEditBox("green_edit.png");
	_box->setPosition(Vec2(370, 380));
	_box->setPlaceHolder("ID或用户名");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符
	//输入密码的框
	_box = createEditBox("orange_edit.png");
	_box->setPosition(Vec2(370, 330));
	_box->setPlaceHolder("密码");
	_box->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
}