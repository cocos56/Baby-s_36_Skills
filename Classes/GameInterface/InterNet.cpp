#pragma execution_character_set("utf-8")
#include "InterNet.h"
Scene * InterNet::createScene()
{
	Scene * scene = Scene::create();
	Layer * layer =InterNet::create();
	scene->addChild(layer);
	return scene;
}
bool InterNet::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getWinSize();
	auto bg=Sprite::create("background1.png");
	auto scaleX = size.width/bg->getContentSize().width;
	auto scaleY = size.height/bg->getContentSize().height;
	bg->setScale(scaleX,scaleY);
	bg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(bg);
	return true;
}


