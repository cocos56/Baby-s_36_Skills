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
	if (Connect::_ws) { str = "连接服务器成功，请登录，如果没有账号请先注册。"; }
	else { str = "已与服务器失去连接，请返回服务器连接界面重连"; }
	_logLabel = createLabel(str);
	_logLabel->setPosition(150, 150);
}

void SignInScene::initMenu()
{
	_label = Label::create("登录", QE_Font, 25);
	MenuItemLabel* inItem = MenuItemLabel::create(_label, bind(&SignInScene::signIn, this));
	inItem->setPosition(410, 270);

	_label = Label::create("注册", QE_Font, 25);
	MenuItemLabel* upItem = MenuItemLabel::create(_label, bind(&SignInScene::signUp, this));
	upItem->setPosition(540, 270);

	_label = Label::create("返回", QE_Font, 25);
	MenuItemLabel* backItem = MenuItemLabel::create(_label, bind(&SignInScene::back, this));
	backItem->setPosition(10, 500);
	backItem->setAnchorPoint(Vec2(0, 0));

	Menu* mn = Menu::create(inItem, upItem, backItem, NULL);
	mn->setPosition(0, 0);
	addChild(mn);
}

void SignInScene::signIn()
{

}
void SignInScene::signUp()
{

}

void SignInScene::back()
{
	Director::getInstance()->replaceScene(ConnectServerScene::createScene());
}

void SignInScene::initEditBox()
{
	EditBox* box;
	//输入ID的框
	box = createEditBox("green_edit.png");
	box->setPosition(Vec2(370, 380));
	box->setPlaceHolder("ID或用户名");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符
	//输入密码的框
	box = createEditBox("orange_edit.png");
	box->setPosition(Vec2(370, 330));
	box->setPlaceHolder("密码");
	box->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
}