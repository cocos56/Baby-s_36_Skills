#pragma execution_character_set("utf-8")

#include "SignUpScene.h"

EditBox* SignUpScene::_unBox, * SignUpScene::_nickNameBox, * SignUpScene::_passwordBox;

QE_CreateSceneFromLayer_CPP(SignUpScene);
	paths = { "fonts" };
	QE_SetResourcesSearchDir;

	Connect::connect(Connect::Event::SignUp);

	createLabel("请输入用户名、昵称和密码进行账号注册。");
	_label->setPosition(150, 150);
	_logLabel = _label;

	initMenu();
	initEditBox();
	return true;
}

void SignUpScene::initMenu()
{
	Menu* menu = QMenu::createMenuLabel("注册", bind(&SignUpScene::SignUp, this));
	menu->setPosition(450, 220);
	addChild(menu);
}

void SignUpScene::SignUp()
{
	Connect::createMsg();
	Connect::addMsg("用户名", QE_ToJStr(_unBox->getText()));
	Connect::addMsg("昵称", QE_ToJStr(_nickNameBox->getText()));
	Connect::addMsg("密码", QE_ToJStr(_passwordBox->getText()));
	Connect::sendMsg();
}

void SignUpScene::initEditBox()
{
	//输入用户名的框
	_unBox = _box = createEditBox("green_edit.png");
	_box->setPosition(Vec2(370, 380));
	_box->setPlaceHolder("用户名");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符

	//输入用户名的框
	_nickNameBox = _box = createEditBox("orange_edit.png");
	_box->setPosition(Vec2(370, 330));
	_box->setPlaceHolder("昵称");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符

	//输入密码的框
	_passwordBox = _box = createEditBox("green_edit.png");
	_box->setPosition(Vec2(370, 280));
	_box->setPlaceHolder("密码");
	_box->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
}