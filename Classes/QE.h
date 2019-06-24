#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine/QuickEngine.h"

//宏

//User
#include "AppDelegate.h"

//GameInterface
#include "GameInterface/ResourceLoadScene.h"
#include "GameInterface/LogoScene.h"
#include "GameInterface/GameInterfaceScene.h"

//SingleGame
//动画
#include "SingleGame/animation.h"
//摇杆
#include "SingleGame/HRocker.h"
//实现解析数据
#include "SingleGame/DataParse.h"
#include "SingleGame/Battle.h"
//主场景（入口）
#include "SingleGame/MapOne.h"
//动物园ZOO
#include "SingleGame/MapTwo.h"
//超市SHOOP
#include "SingleGame/MapThere.h"
// 医院HOSP
#include "SingleGame/MapFour.h"
//学校School
#include "SingleGame/MapFive.h"

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
#include "NetWorkGame/NetworkGame/SelectRoleScene.h"
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