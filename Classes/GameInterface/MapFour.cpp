#pragma execution_character_set("utf-8")

#include "MapFour.h"

TMXTiledMap *tileMap2;
HRocker* rocker4;

Scene * MapFour::createScene()
{
	Scene * scene = Scene::create();
	Layer * layer =MapFour::create();
	scene->addChild(layer);
	Layer* Hrockerlayer=HrockerLayer4::create();
	scene->addChild(Hrockerlayer);
	return scene;
}
bool MapFour::init()
{
	if (!Layer::init())
	{
		return false;
	}
	 tileMap2 = TMXTiledMap::create("shop.tmx");
	tileMap2->setAnchorPoint(Vec2::ZERO);
	tileMap2->setPosition(Vec2::ZERO);
	this->addChild(tileMap2);
	

	MenuItemImage *back=MenuItemImage::create("CloseSelected.png","CloseSelected.png",CC_CALLBACK_0(MapFour::backTwo,this));
	back->setPosition(930,100);
	
	auto menu=Menu::create(back,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

  return true;
}
bool HrockerLayer4::init()
{
	if (!Layer::init())
	{
		return false;
	}

	 rocker4 = HRocker::createHRocker("yaogandian.png", "yaogandi.png", ccp(110,80));//其中第一张图片为摇杆的按钮，第二张为背景  
	this->addChild(rocker4, 2);
	rocker4->startRocker(true);

	return true;

}
void MapFour::backTwo()
{
  Director::getInstance()->popScene();
}