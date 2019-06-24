#pragma execution_character_set("utf-8")

#include "MapTwo.h"


TMXTiledMap *tileMap;
TMXLayer  *_collidable2;
HRocker* rocker2;

Scene * MapTwo::createScene()
{
	Scene * scene = Scene::create();
	Layer* layer =MapTwo::create();
	scene->addChild(layer);

	Layer* Hrockerlayer=HrockerLayer2::create();
	scene->addChild(Hrockerlayer);
	return scene;
}


bool MapTwo::init()
{
	if (!Layer::init())
	{
		return false;
	}

	k1=0;
	kj=0;
	j=0;

	tileMap = TMXTiledMap::create("zoo.tmx");
	tileMap->setAnchorPoint(Vec2::ZERO);
	tileMap->setPosition(Vec2::ZERO);
	this->addChild(tileMap);

	UserDefault::getInstance()->setIntegerForKey("level",1);

	_collidable2=tileMap->getLayer("peng1");
	_collidable2->setVisible(false);

	
	
	 chu=Sprite::create("enter.png");
	chu->setPosition(930,100);
	chu->setVisible(false);
	this->addChild(chu);

	auto object=tileMap->getObjectGroup("people1");
	ValueMap map3=object->getObject("hero");
	int x3=map3.at("x").asInt();
	int y3=map3.at("y").asInt();
	 herohrea=Sprite::create("buddy_1_1.png");
	herohrea->setPosition(x3,y3);
	tileMap ->addChild(herohrea,1);

	

	ValueMap map4=object->getObject("herobad");
	int x4=map4.at("x").asInt();
	int y4=map4.at("y").asInt();
	 heroBad=Sprite::create("enermy_1_1.png");
	heroBad->setPosition(x4,y4);
	tileMap ->addChild(heroBad,1);
	
	



	this->scheduleUpdate();

  return true;
}

bool HrockerLayer2::init()
{
	if (!Layer::init())
	{
		return false;
	}

	

	 rocker2 = HRocker::createHRocker("yaogandian.png", "yaogandi.png", ccp(110,80));//其中第一张图片为摇杆的按钮，第二张为背景  
	this->addChild(rocker2, 2);
	rocker2->startRocker(true);


	return true;

}



void MapTwo::update(float f)
{
	if(kj==0)
	{
		if (herohrea->getPosition().x >heroBad->getPosition().x) {
				if(heroBad->isFlippedX() == true)
					heroBad->setFlippedX(false);
			}else{
				if(heroBad->isFlippedX() == false)
					heroBad->setFlippedX(true);
			}
	}

	
	switch (rocker2->rocketDirection)
		{
			case 1:

				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_",5, rocker2->rocketRun,herohrea,1);
				
				
				 p2= movePlayer(Vec2( herohrea->getPosition().x +2, herohrea->getPosition().y),herohrea->getPosition());
		        herohrea->setPosition(p2);
				
				break;
			case  2:
				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_", 5, rocker2->rocketRun,herohrea, 2);
				 p2= movePlayer(Vec2(herohrea->getPosition().x,herohrea->getPosition().y +2),herohrea->getPosition());
		        herohrea->setPosition(p2);
				
				break;
			case 3:
				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_", 5, rocker2->rocketRun,herohrea,3);
			
	            p2= movePlayer(Vec2( herohrea->getPosition().x -2,  herohrea->getPosition().y),herohrea->getPosition());
		        herohrea->setPosition(p2);
				
				break;
			case 4:
				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_", 5, rocker2->rocketRun,herohrea,4);
		    
				 p2= movePlayer(Vec2( herohrea->getPosition().x,  herohrea->getPosition().y -2),herohrea->getPosition());
		        herohrea->setPosition(p2);
				
				
				break;
			default:
				animation::StopAnimation( herohrea);//停止所有动画和运动  
				break;
		}

	auto rectA=herohrea->getBoundingBox();
	auto rectC=chu->getBoundingBox();
	auto rectB=heroBad->getBoundingBox();
	
	
	//kj是记录碰撞
	if (rectA.intersectsRect(rectB)&&kj==0)
	{
	    animation::StopAnimation(heroBad);
		heroBad->stopAllActions();
		this->unschedule(schedule_selector(MapTwo::heroRound));

		//DelayTime::create(3);
		


		auto scens =Battle::createScene();
		Director::getInstance()->pushScene(scens);

		kj=1;

	}

	if (rectA.intersectsRect(rectC)&&chu->isVisible())
	{
		backTwo();
	}
	
	float w=pow(abs((herohrea->getPositionX()-heroBad->getPositionX())),2.0);
	float y=pow(abs((herohrea->getPositionY()-heroBad->getPositionY())),2.0);
	
	float s=sqrt( w+ y);
	
	if(s <=190&&s>=0&&k1==0&&kj==0)
	{
		   heroRound(0.1);
	
           k1=1;
	}

	
	if(kj==1)
	{
	    rocker2->resumeState();
		heroBadRounf(0.1);	
		kj=-1;
	
	}

}

void MapTwo::backTwo()
{
	
	this->unschedule(schedule_selector(MapTwo::heroRound));
	this->unschedule(schedule_selector(MapTwo::heroBadRounf));
	rocker2->stopRocker();
    Director::getInstance()->popScene();

	
}

//实现角色奔跑
void MapTwo::heroBadRounf(float d)
{

	
		 if(heroBad->isFlippedX() == true)
		 {		heroBad->setFlippedX(false);}


		if(heroBad->isFlippedX() == false)
		{		heroBad->setFlippedX(true);}

	    x=-40;
	    y=0;
	
		
		auto move=MoveBy::create(0.1,Point(x,y));
		
		auto ani= animation::getAnimation("walk.plist", "walk.png", "walk_", 5,heroBad,3);
		auto action = Animate::create(ani);
		heroBad->runAction(Sequence::create(action,move, NULL));	

		if(heroBad->getPositionX()<0)
		{
			this->unschedule(schedule_selector(MapTwo::heroBadRounf));
			this->removeChild(heroBad,true);

			chu->setVisible(true);
		}

		this->schedule(schedule_selector(MapTwo::heroBadRounf),0.1);
}


//坏人移动，实现找人移动
void MapTwo::heroRound(float d)
{
	
	
	Point pp= moveBad(true,herohrea->getPosition());
	auto move=MoveBy::create(0.1,pp);
   
    auto ani= animation::getAnimation("enermy_1.plist", "enermy_1.png", "enermy_1_", 5,heroBad,3);
	auto action = Animate::create(ani);
	heroBad->runAction(Sequence::create(action,move, NULL));
	if(kj==0)
	{
	   this->schedule(schedule_selector(MapTwo::heroRound),0.3);
	}
	else
	{
		this->unschedule(schedule_selector(MapTwo::heroRound));
	}
  
}


//坏人移动的算法
Point MapTwo::moveBad(bool active,Point ph)
{
	
		auto s=heroBad;
	 //   //x轴方向移动的距离
		int text1=abs(ph.x-s->getPosition().x);
		int text2=abs(ph.y-s->getPosition().y);
		if(text1>text2)
		{
			x=ph.x-s->getPosition().x>0?40:-40;
			 y=0;
		}
	 //   //y轴方向上移动的距离
		else
		{
			 x=0;
			y=ph.y-s->getPosition().y>0?40:-40;
		}
		return Vec2(x,y);

}



//测试是否可以走
Point  MapTwo::movePlayer(Point p,Point p3)
{
    int x =(p.x)/tileMap->getTileSize().width;
    int y= tileMap->getMapSize().height-(p.y/tileMap->getTileSize().height);
    
    Point currentPoint=Point(x,y);    
    if (x!=tileMap->getMapSize().width && y!=tileMap->getMapSize().height)
    {
        
        int tilegid=_collidable2->getTileGIDAt(currentPoint);
       
        cocos2d::Value value=tileMap->getPropertiesForGID(tilegid);
       
        auto valueStr=value.getDescription();
        
        if (tilegid)
        
        {
           
            if (!value.isNull())
            {
            
                if (valueStr.find("collidable")!=-1)
                {
					return p3;
				
                }
                
            }
        }
        
		return p;
    }
	return p3;
}