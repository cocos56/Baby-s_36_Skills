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

	//1秒 运动到100%
	ProgressTo * progressTo = ProgressTo::create(3,100);
	auto call = CallFunc::create(CC_CALLBACK_0(ResourceLoadScene::LogoScene,this));
	auto sequene = Sequence::create(progressTo,call,NULL);
	timer->runAction(sequene);
	return true;
}
void ResourceLoadScene::LogoScene()
{
	//声明一个场景
	Scene * scene = LogoScene::createScene();
	//翻页动画
	TransitionPageTurn * turn = TransitionPageTurn::create(1,scene,false);
	//替换场景
	Director::getInstance()->replaceScene(turn);
}