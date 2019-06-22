#pragma execution_character_set("utf-8")
#include "MapFive.h"
#include "MapOne.h"
#include "HRocker.h"


TMXTiledMap *tileMap3;
HRocker* rocker5;

Scene * MapFive::createScene()
{
	Scene * scene = Scene::create();
	Layer * layer =MapFive::create();
	scene->addChild(layer);

	Layer* Hrockerlayer=HrockerLayer5::create();
	scene->addChild(Hrockerlayer);
	return scene;
}
bool MapFive::init()
{
	if (!Layer::init())
	{
		return false;
	}
	 tileMap3 = TMXTiledMap::create("school.tmx");
	tileMap3->setAnchorPoint(Vec2::ZERO);
	tileMap3->setPosition(Vec2::ZERO);
	this->addChild(tileMap3);
	

	MenuItemImage *back=MenuItemImage::create("CloseSelected.png","CloseSelected.png",CC_CALLBACK_0(MapFive::backTwo,this));
	back->setPosition(930,100);
	
	auto menu=Menu::create(back,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

  return true;
}
bool HrockerLayer5::init()
{
	if (!Layer::init())
	{
		return false;
	}

	 rocker5 = HRocker::createHRocker("yaogandian.png", "yaogandi.png", ccp(110,80));//其中第一张图片为摇杆的按钮，第二张为背景  
	this->addChild(rocker5, 2);
	rocker5->startRocker(true);

	return true;

}
void MapFive::backTwo()
{
	
  Director::getInstance()->popScene();
}