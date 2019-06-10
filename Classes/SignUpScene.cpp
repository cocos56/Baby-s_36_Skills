#pragma execution_character_set("utf-8")

#include "SignUpScene.h"

Label* SignUpScene::_label, * SignUpScene::_logLabel;
EditBox* SignUpScene::_unBox, * SignUpScene::_nickNameBox, * SignUpScene::_passwordBox;

QE_CreateSceneFromLayer_CPP(SignUpScene);
	paths = { "fonts" };
	QE_SetResourcesSearchDir;

	Connect::connect("注册");

	createLabel("请输入用户名、昵称和密码进行账号注册。");
	_label->setPosition(150, 150);
	_logLabel = _label;

	initMenu();
	initEditBox();
	return true;
}


void SignUpScene::createLabel(string show)
{
	_label = Label::create(show, QE_Font, 24);
	_label->setAnchorPoint(Vec2(0, 0));
	addChild(_label);
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
	EditBox* box;
	//输入用户名的框
	_unBox = box = createEditBox("green_edit.png");
	box->setPosition(Vec2(480, 380));
	box->setPlaceHolder("用户名");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符

	//输入用户名的框
	_nickNameBox = box = createEditBox("orange_edit.png");
	box->setPosition(Vec2(480, 330));
	box->setPlaceHolder("昵称");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符

	//输入密码的框
	_passwordBox = box = createEditBox("green_edit.png");
	box->setPosition(Vec2(480, 280));
	box->setPlaceHolder("密码");
	box->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
}

EditBox* SignUpScene::createEditBox(string normalPngFile)
{
	EditBox* box = EditBox::create(Size(220, 38), Scale9Sprite::create(normalPngFile), Scale9Sprite::create("wite_edit.png"));
	box->setFontName(QE_Font);
	box->setFontSize(25);
	box->setFontColor(Color3B(0, 0, 255));
	box->setPlaceholderFontName(QE_Font);
	box->setPlaceholderFontSize(25);
	box->setPlaceholderFontColor(Color3B(255, 0, 0));
	box->setMaxLength(16);   //设置文本框中文本的最大长度
	box->setInputMode(EditBox::InputMode::SINGLE_LINE);//输入键盘模式,任何符号
	box->setReturnType(EditBox::KeyboardReturnType::DONE);//设置软键盘中回车按钮的样子
	box->setDelegate(this);//开启委托，文本框代理，需要实现EditBoxDelegate代理中的方法，就可以对EditBox进行控制
	addChild(box);
	return box;
}

void SignUpScene::dealServerResponse()
{
	dealServerResponse(QJson::getString("消息"));
}

void SignUpScene::dealServerResponse(string str)
{
	_logLabel->setString(str);
}