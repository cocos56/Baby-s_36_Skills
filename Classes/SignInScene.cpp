#pragma execution_character_set("utf-8")

#include "SignInScene.h"

Label* SignInScene::_label, * SignInScene::_logLabel;
EditBox* SignInScene::_idBox, * SignInScene::_passwordBox;

QE_CreateSceneFromLayer_CPP(SignInScene);
	paths = { "fonts" };
	QE_SetResourcesSearchDir;

	Connect::connect("登录");

	createLabel("请登录，如果没有账号请先注册。");
	_label->setPosition(150, 150);
	_logLabel = _label;

	initMenu();
	initEditBox();
	return true;
}

void SignInScene::createLabel(string show)
{
	_label = Label::create(show, QE_Font, 24);
	_label->setAnchorPoint(Vec2(0, 0));
	addChild(_label);
}

void SignInScene::initMenu()
{
	_label = Label::create("登录", QE_Font, 25);
	MenuItemLabel* inItem = MenuItemLabel::create(_label, bind(&SignInScene::SignIn, this));
	inItem->setPosition(410, 270);

	_label = Label::create("注册", QE_Font, 25);
	MenuItemLabel* upItem = MenuItemLabel::create(_label, bind(&SignInScene::SignUp, this));
	upItem->setPosition(540, 270);

	Menu* mn = Menu::create(inItem, upItem, NULL);
	mn->setPosition(0, 0);
	addChild(mn);
}

void SignInScene::SignIn()
{
	//JValue& value = doc["type"];
	//value.SetInt(123);
	//value = doc["type"].GetInt();
	//if (value.IsInt())
	//{
	//	CCLOG("type is %d, doc[type] is %d", value.GetInt(), doc["type"].GetInt());
	//}
}
void SignInScene::SignUp()
{

}

void SignInScene::initEditBox()
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

EditBox* SignInScene::createEditBox(string normalPngFile)
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

void SignInScene::dealServerResponse()
{
	dealServerResponse(QJson::getString("消息"));
}

void SignInScene::dealServerResponse(string str)
{
	_logLabel->setString(str);
}