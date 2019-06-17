#pragma execution_character_set("utf-8")

#include "SignInScene.h"

EditBox* SignInScene::_idBox, * SignInScene::_passwordBox;
string SignInScene::_nickName = "null";

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
}

void SignInScene::initSprite()
{
	QE_addBgSpriteToThis;
}

void SignInScene::initLabel(){ NW_InitLogLabel(150, 110); }

void SignInScene::initMenu()
{
	int x, y;
	x = 380, y = 270;
	QE_CreateLabelMenu(x, y, "登录", SignInScene, signIn);
	x = 530, y = 270;
	QE_CreateLabelMenuAgain(x, y, "注册", SignInScene, signUp);
	x = 10, y = 500;
	QE_CreateLabelMenuAgain(x, y, "返回", SignInScene, back);
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
	_idBox = _box = createEditBox("editBox3.png");
	_box->setPosition(Vec2(370, 380));
	_box->setPlaceHolder("用户名");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符
	//输入密码的框
	_passwordBox = _box = createEditBox("editBox4.png");
	_box->setPosition(Vec2(370, 330));
	_box->setPlaceHolder("密码");
	_box->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
}