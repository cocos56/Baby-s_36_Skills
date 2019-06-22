#pragma execution_character_set("utf-8")
#include "MapOne.h"


TMXTiledMap *_tileMap;
TMXLayer  *_collidable;
int k=0;

HRocker* rocker;

Scene * MapOne::createScene()
{
	Scene * scene = Scene::create();
	Layer * layer = MapOne::create();
	scene->addChild(layer);

	Layer* Hrockerlayer=HrockerLayer::create();
	scene->addChild(Hrockerlayer);

	return scene;
}
bool MapOne::init()
{
	if (!Layer::init())
	{
		return false;
	}


	
	Size size=Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	


	_tileMap = TMXTiledMap::create("MYMAP1.TMX");
	_tileMap->setAnchorPoint(Vec2::ZERO);
	_tileMap->setPosition(Vec2::ZERO);
	this->addChild(_tileMap);

	//设置遥感







	_collidable=_tileMap->getLayer("peng");
	_collidable->setVisible(false);


	


	auto object=_tileMap->getObjectGroup("people");
	ValueMap map=object->getObject("hero");
	int x=map.at("x").asInt();
	int y=map.at("y").asInt();

	hero=Sprite::create("walk_1.png");
	

	hero->setPosition(x,y);
	_tileMap->addChild(hero,1);

	ValueMap map1=object->getObject("zoo");
	int x1=map1.at("x").asInt();
	int y1=map1.at("y").asInt();

	 _player1=Sprite::create("CloseNormal.png");
	_player1->setPosition(x1,y1);
	_tileMap->addChild(_player1,1);
	
	ValueMap map2=object->getObject("hosp");
	int x2=map2.at("x").asInt();
	int y2=map2.at("y").asInt();
	 _player2=Sprite::create("CloseNormal.png");
	_player2->setPosition(x2,y2);
	_tileMap->addChild(_player2,1);

	ValueMap map3=object->getObject("shop");
	int x3=map3.at("x").asInt();
	int y3=map3.at("y").asInt();
	_player3=Sprite::create("CloseNormal.png");
	_player3->setPosition(x3,y3);
	_tileMap->addChild(_player3,1);

	ValueMap map4=object->getObject("school");
	int x4=map4.at("x").asInt();
	int y4=map4.at("y").asInt();
    _player4=Sprite::create("CloseNormal.png");
	_player4->setPosition(x4,y4);
	_tileMap->addChild(_player4,1);
	
    

	

	


	
	auto flower=ParticleSystemQuad::create("flower.plist");
	flower->setPositionType(ParticleSystem::PositionType::GROUPED);
	flower->setPosition(350,150);
	this->addChild(flower);




	this->scheduleUpdate();


    return true;
}

bool HrockerLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	 rocker = HRocker::createHRocker("yaogandian.png", "yaogandi.png", ccp(110,80));//其中第一张图片为摇杆的按钮，第二张为背景  
	this->addChild(rocker, 2);
	rocker->startRocker(true);

	return true;

}



void  MapOne::update(float f)
{
	auto rectA=hero->getBoundingBox();
	auto  rectB=_player1->getBoundingBox();
	auto rectC=_player2->getBoundingBox();
	auto rectD=_player3->getBoundingBox();
	auto rectE=_player4->getBoundingBox();
	
	
    if (rectA.intersectsRect(rectC)&&k==0)
	{
		Director::getInstance()->getScheduler()->autorelease();
		MapOne::back1();
		k=90;
		
	}
	else  if (rectA.intersectsRect(rectD)&&k==0)
	{
		Director::getInstance()->getScheduler()->autorelease();
		MapOne::back2();
		k=90;
		
	}
	  else   if (rectA.intersectsRect(rectE)&&k==0)
	{
		Director::getInstance()->getScheduler()->autorelease();
		MapOne::back3();
		k=90;
		
	}
	  else  if (rectA.intersectsRect(rectB)&&k==0)
	{
		Director::getInstance()->getScheduler()->autorelease();
		MapOne::back();
		k=90;
	}
	

		switch (rocker->rocketDirection)
		{
			case 1:

				animation::SetAnimation("walk.plist", "walk.png", "walk_",5, rocker->rocketRun,hero,1);
				PlayerPoint(Vec2( this->hero->getPosition().x +2, this->hero->getPosition().y));
				
				if(k!=0)
				{
					k--;
				}
				
				
				break;
			case  2:
				animation::SetAnimation("walk.plist", "walk.png", "walk_", 5, rocker->rocketRun,hero, 2);
		        PlayerPoint(Vec2(this->hero->getPosition().x, this->hero->getPosition().y +2));
				
				if(k!=0)
				{
					k--;
				}
				
				break;
			case 3:
				animation::SetAnimation("walk.plist", "walk.png", "walk_", 5, rocker->rocketRun,hero,3);
				PlayerPoint(Vec2(this->hero->getPosition().x -2, this->hero->getPosition().y));
				
				if(k!=0)
				{
					k--;
				}
				
				break;
			case 4:
				animation::SetAnimation("walk.plist", "walk.png", "walk_", 5, rocker->rocketRun,hero,4);
				PlayerPoint(Vec2(this->hero->getPosition().x, this->hero->getPosition().y -2));
				if(k!=0)
				{
					k--;
				}
				
				
				break;
			default:
				animation::StopAnimation(hero);//停止所有动画和运动  
				break;
		}


	
}





//地图移动
void  MapOne:: MoveMap(Point position)
{
    
    auto winSize=Director::getInstance()->getWinSize();
  
    int x=MAX(position.x, winSize.width/2);
    int y=MAX(position.y, winSize.height/2);    
    auto mapSize=_tileMap->getMapSize();  
    auto tileSize=_tileMap->getTileSize();
    x=MIN(x, mapSize.width * tileSize.width-winSize.width/2);
    y=MIN(y, mapSize.height * tileSize.height - winSize.height/2);
    auto actualPoint=Point(x,y);
    auto centerPoint=Point(winSize.width/2, winSize.height/2);
    auto viewPoint=centerPoint - actualPoint; 
	
    this->setPosition(viewPoint);
	
}



void MapOne::PlayerPoint(Point p)
{
	 movePlayer(p);
	this->MoveMap(p);
}



void MapOne::back()
{

	rocker->resumeState();
	DelayTime::create(3);
	auto scens =MapTwo::createScene();
	this->unscheduleAllSelectors();
	Director::getInstance()->pushScene(scens);
}
void MapOne::back1()
{
	rocker->resumeState();
	
	auto scens = MapThere::createScene();
	
	this->unscheduleAllSelectors();
	
	Director::getInstance()->pushScene(scens);
}
void MapOne::back2()
{
	
	rocker->resumeState();
	DelayTime::create(3);
	auto scens =  MapFour::createScene();
	this->unscheduleAllSelectors();
	Director::getInstance()->pushScene(scens);
}
void MapOne::back3()
{
	rocker->resumeState();
	DelayTime::create(3);
	this->unscheduleAllSelectors();
	auto scens =  MapFive::createScene();
	
	Director::getInstance()->pushScene(scens);
}
void  MapOne::movePlayer(Point p)
{
    int x =(p.x)/_tileMap->getTileSize().width;
    int y= _tileMap->getMapSize().height-(p.y/_tileMap->getTileSize().height);
    
    Point currentPoint=Point(x,y);    
    if (x!= _tileMap->getMapSize().width && y!=_tileMap->getMapSize().height)
    {
        
        int tilegid=_collidable->getTileGIDAt(currentPoint);
       
        cocos2d::Value value=_tileMap->getPropertiesForGID(tilegid);
       
        auto valueStr=value.getDescription();
        
        if (tilegid)
        
        {
           
            if (!value.isNull())
            {
            
                if (valueStr.find("collidable")!=-1)
                {
                    return;
					
                }
                
            }
        }
        
		hero->setPosition(p);
    }
}