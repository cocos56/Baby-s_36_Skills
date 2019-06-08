#include "SignInScene.h"

Label* SignInScene::label, * SignInScene::logLabel;
EditBox* SignInScene::_idBox, * SignInScene::_passwordBox;

QE_CreateSceneFromLayer_CPP(SignInScene);
	paths = { "fonts" };
	QE_SetResourcesSearchDir;

	Connect::connect();

	createLabel("Please sign in if you have signed up, or sign up if you don't have an account yet.");
	label->setPosition(150, 150);
	logLabel = label;

	initMenu();
	initEditBox();
	return true;
}

void SignInScene::createLabel(string show)
{
	label = Label::create(show, QE_Font, 24);
	label->setAnchorPoint(Vec2(0, 0));
	addChild(label);
}

void SignInScene::initMenu()
{
	label = Label::create("sign in", QE_Font, 25);
	MenuItemLabel* inItem = MenuItemLabel::create(label, bind(&SignInScene::SignIn, this));
	inItem->setPosition(410, 270);

	label = Label::create("sign up", QE_Font, 25);
	MenuItemLabel* upItem = MenuItemLabel::create(label, bind(&SignInScene::SignUp, this));
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
	box->setPlaceHolder("ID or user name");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符
	//输入密码的框
	box = createEditBox("orange_edit.png");
	box->setPosition(Vec2(480, 330));
	box->setPlaceHolder("password");
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
	box->setInputMode(EditBox::InputMode::ANY);//输入键盘模式,任何符号
	box->setDelegate(this);//开启委托，文本框代理，需要实现EditBoxDelegate代理中的方法，就可以对EditBox进行控制
	addChild(box);
	return box;
}


void SignInScene::editBoxReturn(EditBox* editBox)
{
	CCLOG("editBoxReturn");
	std::string str = editBox->getText();
	CCLOG("%s", str.c_str());
}