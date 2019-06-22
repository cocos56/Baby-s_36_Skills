#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine/QuickEngine.h"

//宏

//User
#include "AppDelegate.h"

//GameInterface
#include "GameInterface/ResourceLoadScene.h"
#include "GameInterface/star.h"
#include "GameInterface/begin.h"

//SingleGame
#include "SingleGame/animation.h"
#include "SingleGame/HRocker.h"
#include "SingleGame/DataParse.h"
#include "SingleGame/Battle.h"
#include "GameInterface/MapOne.h"
#include "GameInterface/MapTwo.h"
#include "GameInterface/MapThere.h"
#include "GameInterface/MapFour.h"
#include "GameInterface/MapFive.h"

//NetWorkGame
#include "NetWorkGame/NetworkBase/Connect.h"
#include "NetWorkGame/NetworkBase/NetworkBaseScene.h"
#include "NetWorkGame/ConnectServer/ConnectServerScene.h"
#include "NetWorkGame/SignIn/SignInScene.h"
#include "NetWorkGame/SignUp/SignUpScene.h"
#include "NetWorkGame/SelectRooms/RoomsInfo.h"
#include "NetWorkGame/SelectRooms/GetRoomsScene.h"
#include "NetWorkGame/SelectRooms/CreateRoomScene.h"
#include "NetWorkGame/SelectRooms/JoinRoomScene.h"
#include "NetWorkGame/SelectRooms/SelectRoleScene.h"
#include "NetWorkGame/NetworkGame/WaitingNetworkGameScene.h"
#include "NetWorkGame/NetworkGame/NetworkGameScene.h"
#include "NetWorkGame/NetworkGame/NetworkGameOverScene.h"


//test
#if 1
	#include "Test\HelloWorldScene.h"
	#include "Test\SocketIOTestLayer.h"
	#include "Test\HttpTest.h"
	#include "Test\WebSocketTestLayer.h"
	#include "Test\SignInSceneTest.h"
#endif // 1