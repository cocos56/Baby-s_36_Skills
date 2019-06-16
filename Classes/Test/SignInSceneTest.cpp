#pragma execution_character_set("utf-8")

#include "SignInSceneTest.h"

EditBox* SignInSceneTest::_idBox, * SignInSceneTest::_passwordBox;

QE_CreateSceneFromLayer_CPP(SignInSceneTest);
	paths = { "fonts" };
	QE_SetResourcesSearchDir;

	//Connect::connect("登录测试");

	createLabel("请登录，如果没有账号请先注册。");
	_label->setPosition(150, 150);
	_logLabel = _label;

	initMenu();
	initEditBox();
	return true;
}

void SignInSceneTest::initMenu()
{
	_label = Label::create("登录", QE_Font, 25);
	MenuItemLabel* inItem = MenuItemLabel::create(_label, bind(&SignInSceneTest::SignIn, this));
	inItem->setPosition(410, 270);

	_label = Label::create("注册", QE_Font, 25);
	MenuItemLabel* upItem = MenuItemLabel::create(_label, bind(&SignInSceneTest::SignUp, this));
	upItem->setPosition(540, 270);

	Menu* mn = Menu::create(inItem, upItem, NULL);
	mn->setPosition(0, 0);
	addChild(mn);
}

void SignInSceneTest::SignIn()
{

}
void SignInSceneTest::SignUp()
{

}

void SignInSceneTest::initEditBox()
{
	EditBox* box;
	//输入ID的框
	box = createEditBox("green_edit.png");
	box->setPosition(Vec2(480, 380));
	box->setPlaceHolder("ID或用户名");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符
	//输入密码的框
	box = createEditBox("orange_edit.png");
	box->setPosition(Vec2(480, 330));
	box->setPlaceHolder("密码");
	box->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
}