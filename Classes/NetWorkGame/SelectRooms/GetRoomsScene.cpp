#pragma execution_character_set("utf-8")

#include "GetRoomsScene.h"

Label* GetRoomsScene::_roomName, * GetRoomsScene::_roomCreator;
string GetRoomsScene::_name = "1" , GetRoomsScene::_creator = "null";

QE_SINGLETON2_CPP(GetRoomsScene);

QE_CreateSceneFromLayer_CPP(GetRoomsScene);
paths = { "fonts" , "GetRoomsScene" };
QE_SetResourcesSearchDir;
QE_addBgSprite;

	_instance = this;

	Connect::connect(Connect::Event::GetRooms);
	
	initLabel();
	initMenu();

	RoomsInfo::initScrollView(this);
	return true;
}

void GetRoomsScene::dealServerResponse(int statusCode)
{
	if (statusCode == 411){ RoomsInfo::setRoomInfo(QJson::getString("nm"), QJson::getString("creator")); }
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
	QMessageBox(status);
}

void GetRoomsScene::initLabel(){ NW_InitLogLabel(150, 80); }

void GetRoomsScene::initMenu()
{
	QE_CreateLabelMenu(460, 180, "创建房间", GetRoomsScene, createRoom);
	QE_CreateLabelMenu(330, 180, "加入房间", GetRoomsScene, joinRoom);
	QE_CreateLabelMenu(10, 500, "返回", GetRoomsScene, back);
}

void GetRoomsScene::createRoom(){ QE_ReplaceScene(CreateRoomScene); }

void GetRoomsScene::joinRoom(){ QE_ReplaceScene(JoinRoomScene); }

void GetRoomsScene::back() { QE_ReplaceScene(SignInScene); };