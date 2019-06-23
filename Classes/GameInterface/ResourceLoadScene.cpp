#pragma execution_character_set("utf-8")

#include "ResourceLoadScene.h"

Scene * ResourceLoadScene::createScene()
{
	Scene * scene = Scene::create();
	Layer * layer = ResourceLoadScene::create();
	scene->addChild(layer);
	return scene;
}
bool ResourceLoadScene::init()
{
	//初始化父类的构造函数，是的话就操作，否的话就return false
	if (!Layer::init())
	{
		return false;
	}

	Size size = Director::getInstance()->getWinSize();//获取屏幕的大小
	Sprite * bg = Sprite::create("bgr.png");//背景
	//让背景图片与屏幕适配
	//auto与id的区别：auto是智能指针，可以自动识别后面参数的类型
	auto scaleX = size.width/bg->getContentSize().width;
	auto scaleY = size.height/bg->getContentSize().height;
	bg->setScale(scaleX,scaleY);//缩放
	bg->setPosition(Vec2(size.width/2,size.height/2));//设置位置
	this->addChild(bg);//添加父试图

	


	auto  *ditu = Sprite::create("0%.png");
	ditu->setPosition(Vec2(size.width / 2, size.height / 2-100));
	this->addChild(ditu);
	
	

	Sprite * timerSp = Sprite::create("loading.png");//创建精灵
	ProgressTimer * timer = ProgressTimer::create(timerSp);//进度条
	timer->setPosition(Vec2(size.width/2,size.height/2-100));//设置位置
	/*
	setBarChangeRate(Vec2(1,0))和setMidpoint(Vec2(0,1))共同决定设置进度条的展开方向:
	第一个参数为0表示水平方向没有展开效果，为1表示水平方向有展开效果；
	第二个参数为0表示垂直方向没有展开效果，为1表示垂直方向有展开效果。
	(1,0):x轴方向从左向右展开；(0,1)从下向上展开；（0,0）没有展开效果；（1,1）从左下角向右向上展开。
	*/
	timer->setBarChangeRate(Vec2(1,0));
	timer->setMidpoint(Vec2(0,1));//设置基准点（展开的从左边开始）
	timer->setType(ProgressTimer::Type::BAR);//设置进度条类型（条形）
	timer->setPercentage(0);//设置进度条百分比 当前所显示的
	this->addChild(timer);

	auto* car = Sprite::create("car.png");
	car->setPosition(Vec2(50, size.height / 2-100));
	this->addChild(car);
	auto yi = MoveTo::create(3, Vec2(850, size.height / 2-100));
	car->runAction(yi);
	auto new_Node = Node::create();
	new_Node->setPosition(Vec2(0, 0));
	new_Node->setTag(1);
	this->addChild(new_Node, 1);


	//添加进度条背景精灵grassDownSprite（红色的）
	/*auto bg_bar = Sprite::create("progess_bar2.png");
	barSize = bg_bar->getContentSize();
	bg_bar->setAnchorPoint(Vec2(0, 0));
	bg_bar->setPosition((visibleSize.width - barSize.width / 2) / 2, 80);
	//创建标签
	bg_bar->setTag(0);
	bg_bar->setScale(0.5);
	new_Node->addChild(bg_bar, 0);

	//添加进度条（黄色的）
	auto bar = LoadingBar::create("progess_bar1.png");
	bar->setScale(0.5);
	bar->setAnchorPoint(Vec2(0, 0));
	bar->setPosition(Vec2((visibleSize.width - barSize.width / 2) / 2, 80));
	bar->setDirection(LoadingBar::Direction::LEFT);
	bar->setTag(3);
	this->addChild(bar, 1);


	//添加球精灵，位于的进度条上方，设置节点数为2
	ball = Sprite::create("ball.png");
	//ball->setAnchorPoint(Vec2(0, 0));
	ball->setScale(0.5);
	ball->setPosition((visibleSize.width - barSize.width / 2) / 2 - ball->getContentSize().width / 8, 105);

	ball->setAnchorPoint(Vec2(0.5, 0.5));
	auto repeatforeve = RepeatForever::create(RotateBy::create(0.1, 120));
	ball->runAction(repeatforeve);

	this->addChild(ball, 2);

	//定时器；完成进度条的运行和球精灵的运动
	d = barSize.width / 2 / 100 / 4;
	schedule(schedule_selector(LoadingInterface::update), 1.0 / 90);*/



	//1秒 运动到100%
	ProgressTo * progressTo = ProgressTo::create(3,100);
	auto call = CallFunc::create(CC_CALLBACK_0(ResourceLoadScene::startScene,this));
	auto sequene = Sequence::create(progressTo,call,NULL);
	timer->runAction(sequene);

	/*Label * lable = Label::createWithSystemFont("Loading","",40);
	lable->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(lable);*/
	return true;
}
void ResourceLoadScene::startScene()
{
	//声明一个场景
	Scene * scene = star::createScene();
	//翻页动画
	TransitionPageTurn * turn = TransitionPageTurn::create(1,scene,false);
	//替换场景
	Director::getInstance()->replaceScene(turn);
}