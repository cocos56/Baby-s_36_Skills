#pragma execution_character_set("utf-8")

#include "GetRoomsScene.h"

Label* GetRoomsScene:: _roomID, * GetRoomsScene::_roomName, * GetRoomsScene::_roomCreater;

QE_SINGLETON2_CPP(GetRoomsScene);

QE_CreateSceneFromLayer_CPP(GetRoomsScene);
paths = { "fonts" , "GetRoomsScene" };
QE_SetResourcesSearchDir;
QE_addBgSpriteToThis;

	_instance = this;

	Connect::connect(Connect::Event::GetRooms);

	initLabel();
	initMenu();
	getRoomInfo();
	return true;
}

void GetRoomsScene::dealServerResponse(int statusCode)
{
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
	QMessageBox(status);
}
void GetRoomsScene::getRoomInfo()
{
	Connect::createMsg();
	Connect::sendMsg();
}

void GetRoomsScene::initLabel()
{
	auto s = Scale9Sprite::create("green_edit.png");  //设置ScrollView背景，便于查看容器大小
	s->setContentSize(Size(230, 215));
	s->setPosition(Vec2(450, 410));
	addChild(s);

	createLabel("房间信息");
	_label->setPosition(400, 480);
	createLabel("房间名：");
	_label->setPosition(350, 380);
	_roomName = createLabel("");
	_roomName->setPosition(450, 380);
	createLabel("创建者：");
	_label->setPosition(350, 330);
	_roomCreater = createLabel("");
	_roomCreater->setPosition(450, 330);

	NW_InitLogLabel(150, 100);
}

void GetRoomsScene::initMenu()
{
	QE_CreateLabelMenu(460, 220, "创建房间", GetRoomsScene, createRoom);
	QE_CreateLabelMenuAgain(330, 220, "加入房间", GetRoomsScene, joinRoom);
	QE_CreateLabelMenuAgain(10, 500, "返回", GetRoomsScene, back);
}

void GetRoomsScene::createRoom(){ QE_ReplaceScene(CreateRoomScene); }

void GetRoomsScene::joinRoom(){ QE_ReplaceScene(JoinRoomScene); }

void GetRoomsScene::back() { QE_ReplaceScene(SignInScene); };