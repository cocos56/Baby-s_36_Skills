#pragma execution_character_set("utf-8")

#include "star.h"
#include "begin.h"
Scene * star::createScene()
{
	Scene * scene = Scene::create();
	Layer * layer = star::create();
	scene->addChild(layer);
	return scene;
}
bool star::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size size = Director::getInstance()->getWinSize();
	auto bg=Sprite::create("back.png");
	auto scaleX = size.width/bg->getContentSize().width;
	auto scaleY = size.height/bg->getContentSize().height;
	bg->setScale(scaleX,scaleY);
	bg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(bg);
	
	auto yi=Sprite::create("logo.png");
    yi->setPosition(480,320);
	yi->setScale(1);
	this->addChild(yi);
	auto call = CallFunc::create(CC_CALLBACK_0(star::startScene,this));
	auto sequene = Sequence::create(JumpTo::create(1,Vec2(480,330),50,1),FadeOut::create(0.5),call,NULL);
	yi->runAction(sequene);
	return true;
}
void star::startScene()
{
	Scene * scene = begin::createScene();
	TransitionScene * turn = TransitionFadeTR::create(1,scene);
	Director::getInstance()->replaceScene(turn);
}