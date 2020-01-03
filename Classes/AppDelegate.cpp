#pragma execution_character_set("utf-8")

#include "AppDelegate.h"

QE_get_winSize;

static Size designResolutionSize = winSize;
static Size smallResolutionSize = winSize;
static Size mediumResolutionSize = winSize;
static Size largeResolutionSize = winSize;

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Baby's_36_Skills", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Baby's_36_Skills");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
	Scene* scene;

	//游戏资源加载场景
	scene = ResourceLoadScene::createScene();
	//Logo展示场景
	//scene = LogoScene::createScene();
	//游戏主面板界面
	//scene = GameInterfaceScene::createScene();

	//主场景（入口）
	//scene = MapOne::createScene();
	//动物园场景
	//scene = MapTwo::createScene();
	//医院场景
	//scene = MapThere::createScene();
	//商店场景
	//scene = MapFour::createScene();
	//学校场景
	//scene = MapFive::createScene();
	//坏人诱骗场景
	//scene = Battle::createScene();
	
	//连接服务器界面
	//scene = ConnectServerScene::createScene();
	//登录界面
	//scene = SignInScene::createScene();
	//注册界面
	//scene = SignUpScene::createScene();
	//获取房间界面
	//scene = GetRoomsScene::createScene();
	//创建房间界面
	//scene = CreateRoomScene::createScene();
	//加入房间界面
	//scene = JoinRoomScene::createScene();
	//选择角色界面
	//scene = SelectRoleScene::createScene();
	//等待网络游戏开始界面
	//scene = WaitingNetworkGameScene::createScene();
	//网络游戏界面
	//scene = NetworkGameScene::createScene();
	//网络游戏结束界面
	//scene = NetworkGameOverScene::createScene();

	//scene = HelloWorld::createScene();
	//scene = SignInSceneTest::createScene();
	//scene = SocketIOTestLayer::createScene();
	//scene = HttpTest::createScene();
	//scene = WebSocketTestLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}