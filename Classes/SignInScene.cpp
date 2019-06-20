#pragma execution_character_set("utf-8")

#include "SignInScene.h"

EditBox* SignInScene::_unBox, * SignInScene::_passwordBox;
string SignInScene::_un = "null";

QE_SINGLETON2_CPP(SignInScene);

QE_CreateSceneFromLayer_CPP(SignInScene);
	paths = { "fonts", "SignInScene" };
	QE_SetResourcesSearchDir;

	_instance = this;

	Connect::connect(Connect::Event::SignIn);

	initSprite();
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
	if (statusCode == 271) { QE_ReplaceScene(GetRoomsScene); }
}

void SignInScene::initSprite()
{
	QE_addBgSprite;
}

void SignInScene::initLabel(){ NW_InitLogLabel(150, 110); }

void SignInScene::initMenu()
{
	QE_CreateLabelMenu(380, 270, "登录", SignInScene, signIn);
	QE_CreateLabelMenu(530, 270, "注册", SignInScene, signUp);
	QE_CreateLabelMenu(10, 500, "返回", SignInScene, back);
}

void SignInScene::signIn()
{
	Connect::createMsg();
	_un = _unBox->getText();
	Connect::addMsg("un", _unBox->getText());
	Connect::addMsg("pw", _passwordBox->getText());
	Connect::sendMsg();
}

void SignInScene::signUp() { QE_ReplaceScene(SignUpScene); };

void SignInScene::back() { QE_ReplaceScene(ConnectServerScene); };

void SignInScene::initEditBox()
{
	//输入ID的框
	_unBox = _box = createEditBox("editBox.png", "editBoxPressed.png");
	_box->setPosition(Vec2(370, 380));
	_box->setPlaceHolder("用户名");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符
	//输入密码的框
	_passwordBox = _box = createEditBox("editBox.png", "editBoxPressed.png");
	_box->setPosition(Vec2(370, 330));
	_box->setPlaceHolder("密码");
	_box->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
}