#pragma execution_character_set("utf-8")

#include "SelectRoomsScene.h"

EditBox* SelectRoomsScene::_unBox, * SelectRoomsScene::_nickNameBox, * SelectRoomsScene::_passwordBox;

QE_SINGLETON2_CPP(SelectRoomsScene);

QE_CreateSceneFromLayer_CPP(SelectRoomsScene);
paths = { "fonts" };
QE_SetResourcesSearchDir;

	_instance = this;

	Connect::connect(Connect::Event::GetRooms);

	initLabel();
	initMenu();
	initEditBox();
	return true;
}

void SelectRoomsScene::dealServerResponse(int statusCode)
{
	NetworkBaseScene::dealServerResponse(statusCode);
	if (statusCode == 381)
	{
		getInstance()->scheduleOnce(schedule_selector(SelectRoomsScene::enterSignInScene), 3.0f);
	}
}

void SelectRoomsScene::enterSignInScene(float f) { QE_ReplaceScene(SignInScene); }

void SelectRoomsScene::initLabel()
{
	string str;
	if (Connect::_ws) { str = GetConnectStatus(SignUpCase1Successful); }
	else { str = GetConnectStatus(SignUpCase1Failed); }
	_logLabel = createLabel(str);
	_logLabel->setPosition(150, 150);
}

void SelectRoomsScene::initMenu()
{
	QE_CreateLabelMenu(450, 220, "创建房间", SelectRoomsScene, signUp);
	QE_CreateLabelMenuAgain(10, 500, "返回", SelectRoomsScene, back);
}

void SelectRoomsScene::signUp()
{
	//Connect::createMsg();
	//Connect::addMsg("un", QE_ToJStr(_unBox->getText()));
	//Connect::addMsg("nn", QE_ToJStr(_nickNameBox->getText()));
	//Connect::addMsg("pw", QE_ToJStr(_passwordBox->getText()));
	//Connect::sendMsg();
}

void SelectRoomsScene::back() { QE_ReplaceScene(SignInScene); };

void SelectRoomsScene::initEditBox()
{
	////输入用户名的框
	//_nickNameBox = _box = createEditBox("orange_edit.png");
	//_box->setPosition(Vec2(370, 330));
	//_box->setPlaceHolder("昵称");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符

	////输入密码的框
	//_passwordBox = _box = createEditBox("green_edit.png");
	//_box->setPosition(Vec2(370, 280));
	//_box->setPlaceHolder("密码");
	//_box->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
}