#pragma execution_character_set("utf-8")

#include "GetRoomsScene.h"

Label* GetRoomsScene::_roomName, * GetRoomsScene::_roomCreator;
string GetRoomsScene::_name = "null" , GetRoomsScene::_creator = "null";

QE_SINGLETON2_CPP(GetRoomsScene);

QE_CreateSceneFromLayer_CPP(GetRoomsScene);
paths = {"GetRoomsScene" };
QE_SetResourcesSearchDir;
QE_addBgSprite;

	_instance = this;
	
	initMenu();

	RoomsInfo::initScrollView(this);
	return true;
}

void GetRoomsScene::dealServerResponse(int statusCode)
{
	if (statusCode == 411){
		_name = QJson::getString("nm");
		_creator = QJson::getString("creator");
		RoomsInfo::setRoomInfo(_name, _creator);
	}
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
	QMessageBox(status);
	
}

void GetRoomsScene::initLabel(){ 
	NW_InitLogLabel(300, 25);
	_logLabel->setColor(Color3B::WHITE);
}

void GetRoomsScene::initMenu()
{
	QE_CreateSpriteMenu(710, 160, "createbutton.png", GetRoomsScene, createRoom);
	QE_CreateSpriteMenu(240, 160, "joinbutton.png", GetRoomsScene, joinRoom);
	QE_CreateLabelMenu(10, 500, "返回", GetRoomsScene, back);
}

void GetRoomsScene::createRoom(){ QE_ReplaceScene(CreateRoomScene); }

void GetRoomsScene::joinRoom(){ QE_ReplaceScene(JoinRoomScene); }

void GetRoomsScene::back() { QE_ReplaceScene(SignInScene); };

void GetRoomsScene::onEnterTransitionDidFinish(){
	Layer::onEnterTransitionDidFinish();
	Connect::connect(Connect::Event::GetRooms);
	initLabel();
}