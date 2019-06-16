#pragma execution_character_set("utf-8")

#include "SignInScene.h"

EditBox* SignInScene::_idBox, * SignInScene::_passwordBox;

QE_SINGLETON2_CPP(SignInScene);

QE_CreateSceneFromLayer_CPP(SignInScene);
	paths = { "fonts" };
	QE_SetResourcesSearchDir;

	_instance = this;

	Connect::connect(Connect::Event::SignIn);

	initLabel();
	initMenu();
	initEditBox();
	return true;
}

void SignInScene::dealServerResponse(int statusCode)
{
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
	QMessageBox(status);
}

void SignInScene::initLabel(){ NW_InitLogLabel(150, 150); }

void SignInScene::initMenu()
{
	QE_CreateLabelMenu(380, 270, "登录", SignInScene, signIn);
	QE_CreateLabelMenuAgain(530, 270, "注册", SignInScene, signUp);
	QE_CreateLabelMenuAgain(10, 500, "返回", SignInScene, back);
}

void SignInScene::signIn()
{
	Connect::createMsg();
	Connect::addMsg("un", QE_ToJStr(_idBox->getText()));
	Connect::addMsg("pw", QE_ToJStr(_passwordBox->getText()));
	Connect::sendMsg();
}

void SignInScene::signUp() { QE_ReplaceScene(SignUpScene); };

void SignInScene::back() { QE_ReplaceScene(ConnectServerScene); };

void SignInScene::initEditBox()
{
	//输入ID的框
	_idBox = _box = createEditBox("green_edit.png");
	_box->setPosition(Vec2(370, 380));
	_box->setPlaceHolder("ID或用户名");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符
	//输入密码的框
	_passwordBox = _box = createEditBox("orange_edit.png");
	_box->setPosition(Vec2(370, 330));
	_box->setPlaceHolder("密码");
	_box->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
}