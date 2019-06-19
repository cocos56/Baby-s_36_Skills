#pragma execution_character_set("utf-8")

#include "SignUpScene.h"

EditBox* SignUpScene::_unBox, * SignUpScene::_passwordBox;

QE_SINGLETON2_CPP(SignUpScene);

QE_CreateSceneFromLayer_CPP(SignUpScene);
	paths = { "fonts", "SignInScene" };
	QE_SetResourcesSearchDir;
	QE_addBgSprite;

	_instance = this;

	Connect::connect(Connect::Event::SignUp);

	initLabel();
	initMenu();
	initEditBox();
	return true;
}

void SignUpScene::dealServerResponse(int statusCode)
{
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
	QMessageBox(status);
	if (statusCode == 381) { QE_ReplaceScene(SignInScene); }
}

void SignUpScene::initLabel(){ NW_InitLogLabel(150, 150); }

void SignUpScene::initMenu()
{
	QE_CreateLabelMenu(450, 250, "注册", SignUpScene, signUp);
	QE_CreateLabelMenu(10, 500, "返回", SignUpScene, back);
}

void SignUpScene::signUp()
{
	Connect::createMsg();
	Connect::addMsg("un", QE_ToJStr(_unBox->getText()));
	Connect::addMsg("pw", QE_ToJStr(_passwordBox->getText()));
	Connect::sendMsg();
}

void SignUpScene::back() { QE_ReplaceScene(SignInScene); };

void SignUpScene::initEditBox()
{
	//输入用户名的框
	_unBox = _box = createEditBox("editBox.png", "editBoxPressed.png");
	_box->setPosition(Vec2(370, 380));
	_box->setPlaceHolder("用户名");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符

	//输入密码的框
	_passwordBox = _box = createEditBox("editBox.png", "editBoxPressed.png");
	_box->setPosition(Vec2(370, 320));
	_box->setPlaceHolder("密码");
	_box->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
}