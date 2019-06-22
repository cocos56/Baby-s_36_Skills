#pragma execution_character_set("utf-8")

#include "MapThere.h"

TMXTiledMap *tileMap1;
HRocker* rocker3;


Scene * MapThere::createScene()
{
	Scene * scene = Scene::create();
	Layer * layer =MapThere::create();
	scene->addChild(layer);
	Layer* Hrockerlayer=HrockerLayer3::create();
	scene->addChild(Hrockerlayer);
	return scene;
}
bool HrockerLayer3::init()
{
	if (!Layer::init())
	{
		return false;
	}

	 rocker3 = HRocker::createHRocker("yaogandian.png", "yaogandi.png", ccp(110,80));//其中第一张图片为摇杆的按钮，第二张为背景  
	this->addChild(rocker3, 2);
	rocker3->startRocker(true);

	return true;

}
bool MapThere::init()
{
	if (!Layer::init())
	{
		return false;
	}
	 tileMap1 = TMXTiledMap::create("hosp.tmx");
	tileMap1->setAnchorPoint(Vec2::ZERO);
	tileMap1->setPosition(Vec2::ZERO);
	this->addChild(tileMap1);
	

	MenuItemImage *back=MenuItemImage::create("CloseSelected.png","CloseSelected.png",CC_CALLBACK_0(MapThere::backTwo,this));
	back->setPosition(930,100);
	
	auto menu=Menu::create(back,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

  return true;
}
void MapThere::backTwo()
{
    
	Director::getInstance()->popScene();
}