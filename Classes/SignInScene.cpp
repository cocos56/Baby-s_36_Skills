#include "SignInScene.h"

QE_CreateSceneFromLayer_CPP(SignInScene);
	paths = { "fonts" };
	QE_SetResourcesSearchDir;

	Connect::connect();
	initMenu();
	initEditBox();

	//createLabel("连接状态：");
	
	createLabel(QCharsetConvert::GBKToUTF8("失败"));
	createLabel(QE_GTU("失败"));
	
	//createLabel("失败");
	//label = Label::createWithTTF("1", "Marker Felt.ttf", 24);
	//label->setPosition(winSize / 3);
	//addChild(label, 1);
	return true;
}

void SignInScene::createLabel(string show)
{
	label = LabelTTF::create(show, "HannotateSC-W5.ttf", 24);
	label->setPosition(winSize / 3);
	addChild(label, 1);
}

void SignInScene::updateLabel()
{

}

void SignInScene::initMenu()
{
	label = LabelTTF::create("sign in", "Marker Felt.ttf", 25);
	MenuItemLabel* inItem = MenuItemLabel::create(label, CC_CALLBACK_0(SignInScene::SignIn, this));
	inItem->setPosition(410, 270);

	label = LabelTTF::create("sign up", "Marker Felt.ttf", 25);
	MenuItemLabel* upItem = MenuItemLabel::create(label, CC_CALLBACK_0(SignInScene::SignUp, this));
	upItem->setPosition(510, 270);

	Menu* mn = Menu::create(inItem, upItem, NULL);
	mn->setPosition(0, 0);
	addChild(mn);
}

void SignInScene::SignIn()
{

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
	box->setFontName("Marker Felt.ttf");
	box->setFontSize(25);
	box->setFontColor(Color3B(0, 0, 255));
	box->setPlaceholderFontName("Marker Felt.ttf");
	box->setPlaceholderFontSize(25);
	box->setPlaceholderFontColor(Color3B(255, 0, 0));
	box->setMaxLength(16);   //设置文本框中文本的最大长度
	box->setInputMode(EditBox::InputMode::ANY);//输入键盘模式,任何符号
	box->setDelegate(this);//开启委托，文本框代理，需要实现EditBoxDelegate代理中的方法，就可以对EditBox进行控制
	addChild(box);
	return box;
}

//编辑框的键盘编辑事件
void SignInScene::editBoxEditingDidBegin(EditBox* editBox)
{
	CCLOG("editBoxEditingDidBegin");
	CCLOG("%d", editBox->getTag());
}

void SignInScene::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
	CCLOG("editBoxTextChanged");
}

void SignInScene::editBoxEditingDidEnd(EditBox* editBox)
{
	CCLOG("editBoxEditingDidEnd");
}

void SignInScene::editBoxReturn(EditBox* editBox)
{
	CCLOG("editBoxReturn");
	std::string str = editBox->getText();
	CCLOG("%s", str.c_str());
	////向服务器发出消息
	//if (_sioClient != NULL) _sioClient->send(str);
}