#pragma execution_character_set("utf-8")

#include"GameInterfaceScene.h"

QE_CreateSceneFromLayer_CPP(GameInterfaceScene);
	paths = { "." };
	QE_SetResourcesSearchDir;
	Size size = Director::getInstance()->getWinSize();
	auto bg=Sprite::create("GameInterfaceScene.png");
	auto scaleX = size.width/bg->getContentSize().width;
	auto scaleY = size.height/bg->getContentSize().height;
	bg->setScale(scaleX,scaleY);
	bg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(bg);
	MenuItemImage *solo=MenuItemImage::create("bg.png","bg.png",CC_CALLBACK_0(GameInterfaceScene::enterMap,this));
	solo->setPosition(Vec2(size.width/4*2,280));
	
	MenuItemImage *ex=MenuItemImage::create("quit.png","quit.png",CC_CALLBACK_0(GameInterfaceScene::end,this));
	ex->setPosition(Vec2(size.width-35,50));
	
	MenuItemImage *Net=MenuItemImage::create("xianshang1.png","xianshang1.png",CC_CALLBACK_0(GameInterfaceScene::enterNet,this));
	Net->setPosition(Vec2(size.width/4*2,200));
	
	MenuItemImage *music=MenuItemImage::create("set.png","set.png",CC_CALLBACK_0(GameInterfaceScene::setLayer,this));
	music->setPosition(Vec2(size.width/4*2,120));
	
	set=Menu::create(solo,ex,Net,music,NULL);
	set->setPosition(Vec2(0,0));
	//set->setVisible(true);
	this->addChild(set);
	set->setTag(1);
	//startAnimate();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic1.mp3");

	return true;
	
}
void GameInterfaceScene::setLayer( )
{
	//进入回调界面要求原来的菜单不可用
	//set->setVisible(false);
	//添加设置面板
	//this->get
	set->setEnabled(false);

	setBg = Sprite::create("mianban.png");
	setBg->setPosition(480,280);
	this->addChild(setBg);

	//音乐控制的开关菜单
	auto onMusic = MenuItemImage::create("duihao1.png","duihao1.png");
	auto offMusic = MenuItemImage::create("quan.png","quan.png");
	
	auto Music=MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameInterfaceScene::setMusic,this),onMusic,offMusic,NULL);

	
	Music->setPosition(Vec2(setBg->getContentSize().width/2-68,setBg->getContentSize().height/2+20));
	auto menu = Menu::create(Music,NULL);
	menu->setPosition(Vec2::ZERO);

	setBg->addChild(menu);

	//okButton
	Button*okButton = Button::create("ok.png","ok.png","ok.png");
	okButton->addClickEventListener(CC_CALLBACK_0(GameInterfaceScene::setBack,this));
	okButton->setPosition(Vec2(setBg->getContentSize().width-65,60));
	okButton->setScale(0.8);
	setBg->addChild(okButton);

	
	auto onEffect = MenuItemImage::create("duihao1.png","duihao1.png");
	auto offEffect = MenuItemImage::create("quan.png","quan.png");
	auto Effect = MenuItemToggle::create(onEffect);
	Effect->addSubItem(offEffect);
	//上面两条语句可以用替换auto Effect = MenuItemToggle::create(onEffect，offEffect，NULL);
	Effect->setCallback(CC_CALLBACK_1(GameInterfaceScene::setEffect,this));
	Effect->setPosition(Vec2(setBg->getContentSize().width/2+175, setBg->getContentSize().height / 2 + 20));
	auto menu2 = Menu::create(Effect,NULL);
	menu2->setPosition(Vec2::ZERO);
	setBg->addChild(menu2);


	//添加滑动条
	auto slider=Slider::create();
	slider->loadBarTexture("0.png");
	slider->loadSlidBallTextures("aaa.png","aaa.png","aaa.png");
	slider->setPosition(Vec2(setBg->getContentSize().width/2,setBg->getContentSize().height/2-90));
	slider->setScale9Enabled(true);
	//slider->setContentSize(Size(Vec2(200,40)));
	slider->setPercent(50);
	slider->addEventListener(CC_CALLBACK_1(GameInterfaceScene::adjustVolumn,this)); //滑动条的监听回调，时刻检测滑动条的值得改变
	setBg->addChild(slider);
}
void GameInterfaceScene::setBack( )
{
	//设置里 确定 按钮
	set->setEnabled(true);
	setBg->removeFromParent();
}
void GameInterfaceScene::setMusic(Ref* sender)
{
	MenuItemToggle *toggle=(MenuItemToggle *)sender;
	//获取菜单组的下标（0--off， 1--on）
	if(toggle->getSelectedIndex( )==1)
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}
void GameInterfaceScene::setEffect(Ref* sender)
{
	MenuItemToggle *toggle=(MenuItemToggle *)sender;
	if(toggle->getSelectedIndex( )==1 )
	{
		/*长期保存的数据，需要存到json或xml文件，暂时保存的可存到缓存userdefault.xml文件中，
		这里保存暂时的音效状态，下次再玩游戏时给这个数据无关
		*/
		UserDefault::getInstance()->setBoolForKey("onEffect",true);
	}
	else
	{
		UserDefault::getInstance()->setBoolForKey("onEffect",false);
	}
}
void GameInterfaceScene::adjustVolumn(Ref * sender)
{
	Slider *slider=(Slider *)sender;
	log("%d",slider->getPercent());
	//滑动条的值为0-100之间的整数，而音量设置的值在0-1之间。故需要除以100.
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(slider->getPercent()/100);
}

void GameInterfaceScene::enterMap()
{
	Scene * scene = MapOne::createScene();
	//翻页动画
	TransitionPageTurn * turn = TransitionPageTurn::create(1,scene,false);
	//替换场景
	Director::getInstance()->replaceScene(turn);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic2.mp3");
}
void GameInterfaceScene::enterNet()
{
	Scene * scene = ConnectServerScene::createScene();
	//翻页动画
	TransitionPageTurn * turn = TransitionPageTurn::create(1,scene,false);
	//替换场景
	Director::getInstance()->replaceScene(turn);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic2.mp3");
}
void GameInterfaceScene::end()
{
	Director::getInstance()->end();
}