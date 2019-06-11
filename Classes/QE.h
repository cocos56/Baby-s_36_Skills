#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine/QuickEngine.h"

//宏

//User
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "Connect.h"
#include "NetworkBaseScene.h"
#include "ConnectServerScene.h"
#include "SignInScene.h"
#include "SignUpScene.h"
#include "SelectRoomsScene.h"
#include "NetworkGameScene.h"


//test
#if 1
	#include "SocketIOTestLayer.h"
	#include "HttpTest.h"
	#include "WebSocketTestLayer.h"
	#include "SignInSceneTest.h"
#endif // 1