#pragma execution_character_set("utf-8")

#include "CreateRoomScene.h"

EditBox* CreateRoomScene::_nameBox, * CreateRoomScene::_passwordBox;

QE_SINGLETON2_CPP(CreateRoomScene);

QE_CreateSceneFromLayer_CPP(CreateRoomScene);
	paths = { "fonts", "CreateRoomScene" };
	QE_SetResourcesSearchDir;
	QE_addBgSpriteToThis;

	_instance = this;

	Connect::connect(Connect::Event::CreateRoom);

	initLabel();
	initMenu();
	initEditBox();
	return true;
}

void CreateRoomScene::dealServerResponse(int statusCode)
{
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status); 
	QMessageBox(status);
}

void CreateRoomScene::initLabel()
{
	//createLabel("创建房间");
	//_label->setPosition(420, 420);

	NW_InitLogLabel(150, 100);
}

void CreateRoomScene::initMenu()
{
	QE_CreateLabelMenu(420, 260, "确认创建", CreateRoomScene, confirm);
	QE_CreateLabelMenuAgain(10, 500, "返回", CreateRoomScene, back);
}

void CreateRoomScene::confirm()
{
	Connect::createMsg();
	Connect::addMsg("nm", QE_ToJStr(_nameBox->getText()));
	Connect::addMsg("pw", QE_ToJStr(_passwordBox->getText()));
	Connect::addMsg("creator", QE_ToJStr(SignInScene::_nickName.c_str()));
	Connect::sendMsg();
}

void CreateRoomScene::back() { QE_ReplaceScene(GetRoomsScene); };

void CreateRoomScene::initEditBox()
{
	//输入用户名的框
	Sprite* spr = Sprite::create("editBox.png");
	_nameBox = _box = createEditBox("editBox.png", "editBoxPressed.png");
	_box->setSize(spr->getContentSize());
	_box->setPosition(Vec2(370, 360));
	_box->setPlaceHolder("房间名");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符

	//输入密码的框
	_passwordBox = _box = createEditBox("editBox.png", "editBoxPressed.png");
	_box->setSize(spr->getContentSize());
	_box->setPosition(Vec2(370, 290));
	_box->setPlaceHolder("房间密码");
	_box->setInputFlag(EditBox::InputFlag::PASSWORD);////设置文本框显示文本的样式，输入密码标记
}