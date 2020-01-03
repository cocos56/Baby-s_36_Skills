#pragma execution_character_set("utf-8")

#include "MapFour.h"

TMXTiledMap *tileMap4;
HRocker* rocker4;
TMXLayer  *_collidable4;

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

	k1=0;
	kj=0;
	j=0;



	tileMap4 = TMXTiledMap::create("shop.tmx");
	tileMap4->setAnchorPoint(Vec2::ZERO);
	tileMap4->setPosition(Vec2::ZERO);
	this->addChild(tileMap4);
	
	UserDefault::getInstance()->setIntegerForKey("level",3);

	_collidable4=tileMap4->getLayer("peng2");
	_collidable4->setVisible(false);


	 chu=Sprite::create("enter.png");
	chu->setPosition(930,100);
	chu->setVisible(false);
	this->addChild(chu);


	auto object=tileMap4->getObjectGroup("people2");
	ValueMap map4=object->getObject("hero");
	int x3=map4.at("x").asInt();
	int y3=map4.at("y").asInt();
	 herohrea4=Sprite::create("buddy_1_1.png");
	herohrea4->setPosition(x3,y3);
	tileMap4->addChild(herohrea4,1);

	ValueMap map4_1=object->getObject("herbad2");
	int x4=map4_1.at("x").asInt();
	int y4=map4_1.at("y").asInt();

	
	 heroBad4=Sprite::create("enermy_4_1.png");
	heroBad4->setPosition(x4,y4);
	tileMap4->addChild(heroBad4,1);
	
	this->scheduleUpdate();

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
	HrockerLayer4::update(0.1);
	return true;

}


void MapFour::update(float f)
{
	if(kj==0)
	{
		if (herohrea4->getPosition().x >heroBad4->getPosition().x) {
				if(heroBad4->isFlippedX() == true)
					heroBad4->setFlippedX(false);
			}else{
				if(heroBad4->isFlippedX() == false)
					heroBad4->setFlippedX(true);
			}
	}

	
	switch (rocker4->rocketDirection)
		{
			case 1:

				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_",5, rocker4->rocketRun,herohrea4,1);
				
				
				 p2= movePlayer(Vec2( herohrea4->getPosition().x +2, herohrea4->getPosition().y),herohrea4->getPosition());
		        herohrea4->setPosition(p2);
				
				break;
			case  2:
				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_", 5, rocker4->rocketRun,herohrea4, 2);
				 p2= movePlayer(Vec2(herohrea4->getPosition().x,herohrea4->getPosition().y +2),herohrea4->getPosition());
		        herohrea4->setPosition(p2);
				
				break;
			case 3:
				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_", 5, rocker4->rocketRun,herohrea4,3);
			
	            p2= movePlayer(Vec2( herohrea4->getPosition().x -2,  herohrea4->getPosition().y),herohrea4->getPosition());
		        herohrea4->setPosition(p2);
				
				break;
			case 4:
				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_", 5, rocker4->rocketRun,herohrea4,4);
		    
				 p2= movePlayer(Vec2( herohrea4->getPosition().x,  herohrea4->getPosition().y -2),herohrea4->getPosition());
		        herohrea4->setPosition(p2);
				
				
				break;
			default:
				animation::StopAnimation( herohrea4);//停止所有动画和运动  
				break;
		}

	auto rectA=herohrea4->getBoundingBox();
	auto rectB=heroBad4->getBoundingBox();
	auto rectC=chu->getBoundingBox();
	
	//kj是记录碰撞
	if (rectA.intersectsRect(rectB)&&kj==0)
	{
	    animation::StopAnimation(heroBad4);
		heroBad4->stopAllActions();
		this->unschedule(schedule_selector(MapFour::heroRound));

		//DelayTime::create(3);
		


		auto scens =Battle::createScene();
		Director::getInstance()->pushScene(scens);

		kj=1;

	}

	if (rectA.intersectsRect(rectC)&&chu->isVisible())
	{
		backFour();
	}
	
	float w=pow(abs((herohrea4->getPositionX()-heroBad4->getPositionX())),2.0);
	float y=pow(abs((herohrea4->getPositionY()-heroBad4->getPositionY())),2.0);
	
	float s=sqrt( w+ y);
	
	if(s <=190&&s>=0&&k1==0&&kj==0)
	{
		   heroRound(0.1);
	
           k1=1;
	}

	
	if(kj==1)
	{
	    rocker4->resumeState();
		heroBadRounf(0.1);	
		kj=-1;
	
	}

}

void MapFour::backFour()
{
	
	this->unschedule(schedule_selector(MapFour::heroRound));
	this->unschedule(schedule_selector(MapFour::heroBadRounf));
	rocker4->stopRocker();
    Director::getInstance()->popScene();

	
}

//实现角色奔跑
void MapFour::heroBadRounf(float d)
{

	
		 if(heroBad4->isFlippedX() == true)
		 {		heroBad4->setFlippedX(false);}


		if(heroBad4->isFlippedX() == false)
		{		heroBad4->setFlippedX(true);}

	    x=-40;
	    y=0;
	
		
		auto move=MoveBy::create(0.1,Point(x,y));
		
		auto ani= animation::getAnimation("enermy_4.plist", "enermy_4.png", "enermy_4_", 5,heroBad4,3);
		auto action = Animate::create(ani);
		heroBad4->runAction(Sequence::create(action,move, NULL));	

		if(heroBad4->getPositionX()<0)
		{
			this->unschedule(schedule_selector(MapFour::heroBadRounf));
			this->removeChild(heroBad4,true);
			chu->setVisible(true);
		}

		this->schedule(schedule_selector(MapFour::heroBadRounf),0.1);
}


//坏人移动，实现找人移动
void MapFour::heroRound(float d)
{
	
	
	Point pp= moveBad(true,herohrea4->getPosition());
	auto move=MoveBy::create(0.1,pp);
   
    auto ani= animation::getAnimation("enermy_4.plist", "enermy_4.png", "enermy_4_", 5,heroBad4,3);
	auto action = Animate::create(ani);
	heroBad4->runAction(Sequence::create(action,move, NULL));
	if(kj==0)
	{
	   this->schedule(schedule_selector(MapFour::heroRound),0.3);
	}
	else
	{
		this->unschedule(schedule_selector(MapFour::heroRound));
	}
  
}


//坏人移动的算法
Point MapFour::moveBad(bool active,Point ph)
{
	
		auto s=heroBad4;
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
Point  MapFour::movePlayer(Point p,Point p3)
{
    int x =(p.x)/tileMap4->getTileSize().width;
    int y= tileMap4->getMapSize().height-(p.y/tileMap4->getTileSize().height);
    
    Point currentPoint=Point(x,y);    
    if (x!=tileMap4->getMapSize().width && y!=tileMap4->getMapSize().height)
    {
        
        int tilegid=_collidable4->getTileGIDAt(currentPoint);
       
        cocos2d::Value value=tileMap4->getPropertiesForGID(tilegid);
       
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