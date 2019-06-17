#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine/QuickEngine.h"

//宏

//User
#include "AppDelegate.h"
#include "Connect.h"
#include "NetworkBaseScene.h"
#include "ConnectServerScene.h"
#include "SignInScene.h"
#include "SignUpScene.h"
#include "RoomInfo.h"
#include "GetRoomsScene.h"
#include "CreateRoomScene.h"
#include "JoinRoomScene.h"
#include"SelectRoleScene.h"
#include "NetworkGameScene.h"
#include "NetworkGameOverScene.h"


//test
#if 1
	#include "Test\HelloWorldScene.h"
	#include "Test\SocketIOTestLayer.h"
	#include "Test\HttpTest.h"
	#include "Test\WebSocketTestLayer.h"
	#include "Test\SignInSceneTest.h"
#endif // 1