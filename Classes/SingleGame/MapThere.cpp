#pragma execution_character_set("utf-8")

#include "MapThere.h"

TMXTiledMap *tileMap3;
HRocker* rocker3;
TMXLayer  *_collidable3;


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


	k1=0;
	kj=0;
	j=0;


	 tileMap3 = TMXTiledMap::create("hosp.tmx");
	tileMap3->setAnchorPoint(Vec2::ZERO);
	tileMap3->setPosition(Vec2::ZERO);
	this->addChild(tileMap3);
	
	UserDefault::getInstance()->setIntegerForKey("level",2);

	_collidable3=tileMap3->getLayer("peng3");
	_collidable3->setVisible(false);

	 chu=Sprite::create("enter.png");
	chu->setPosition(930,100);
	chu->setVisible(false);
	this->addChild(chu);


	auto object=tileMap3->getObjectGroup("people3");
	ValueMap map3=object->getObject("hero");
	int x3=map3.at("x").asInt();
	int y3=map3.at("y").asInt();
	 herohrea3=Sprite::create("buddy_1_1.png");
	herohrea3->setPosition(x3,y3);
	tileMap3->addChild(herohrea3,1);



	
	ValueMap map4=object->getObject("herbad3");
	int x4=map4.at("x").asInt();
	int y4=map4.at("y").asInt();

	 heroBad3=Sprite::create("enermy_2_1.png");
	heroBad3->setPosition(x4,y4);
	tileMap3 ->addChild(heroBad3,1);
	
	this->scheduleUpdate();

  return true;
}


void MapThere::update(float f)
{
	if(kj==0)
	{
		if (herohrea3->getPosition().x >heroBad3->getPosition().x) {
				if(heroBad3->isFlippedX() == true)
					heroBad3->setFlippedX(false);
			}else{
				if(heroBad3->isFlippedX() == false)
					heroBad3->setFlippedX(true);
			}
	}

	
	switch (rocker3->rocketDirection)
		{
			case 1:

				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_",5, rocker3->rocketRun,herohrea3,1);
				
				
				 p2= movePlayer(Vec2( herohrea3->getPosition().x +2, herohrea3->getPosition().y),herohrea3->getPosition());
		        herohrea3->setPosition(p2);
				
				break;
			case  2:
				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_", 5, rocker3->rocketRun,herohrea3, 2);
				 p2= movePlayer(Vec2(herohrea3->getPosition().x,herohrea3->getPosition().y +2),herohrea3->getPosition());
		        herohrea3->setPosition(p2);
				
				break;
			case 3:
				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_", 5, rocker3->rocketRun,herohrea3,3);
			
	            p2= movePlayer(Vec2( herohrea3->getPosition().x -2,  herohrea3->getPosition().y),herohrea3->getPosition());
		        herohrea3->setPosition(p2);
				
				break;
			case 4:
				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_", 5, rocker3->rocketRun,herohrea3,4);
		    
				 p2= movePlayer(Vec2( herohrea3->getPosition().x,  herohrea3->getPosition().y -2),herohrea3->getPosition());
		        herohrea3->setPosition(p2);
				
				
				break;
			default:
				animation::StopAnimation( herohrea3);//停止所有动画和运动  
				break;
		}

	auto rectA=herohrea3->getBoundingBox();
	auto rectB=heroBad3->getBoundingBox();
	auto rectC=chu->getBoundingBox();
	
	//kj是记录碰撞
	if (rectA.intersectsRect(rectB)&&kj==0)
	{
	    animation::StopAnimation(heroBad3);
		heroBad3->stopAllActions();
		this->unschedule(schedule_selector(MapThere::heroRound));

		//DelayTime::create(3);
		


		auto scens =Battle::createScene();
		Director::getInstance()->pushScene(scens);

		kj=1;

	}

	if (rectA.intersectsRect(rectC)&&chu->isVisible())
	{
		backThere();
	}
	
	float w=pow(abs((herohrea3->getPositionX()-heroBad3->getPositionX())),2.0);
	float y=pow(abs((herohrea3->getPositionY()-heroBad3->getPositionY())),2.0);
	
	float s=sqrt( w+ y);
	
	if(s <=190&&s>=0&&k1==0&&kj==0)
	{
		   heroRound(0.1);
	
           k1=1;
	}

	
	if(kj==1)
	{
	    rocker3->resumeState();
		heroBadRounf(0.1);	
		kj=-1;
	
	}

}

void MapThere::backThere()
{
	
	this->unschedule(schedule_selector(MapThere::heroRound));
	this->unschedule(schedule_selector(MapThere::heroBadRounf));
	rocker3->stopRocker();
    Director::getInstance()->popScene();

	
}

//实现角色奔跑
void MapThere::heroBadRounf(float d)
{

	
		 if(heroBad3->isFlippedX() == true)
		 {		heroBad3->setFlippedX(false);}


		if(heroBad3->isFlippedX() == false)
		{		heroBad3->setFlippedX(true);}

	    x=-40;
	    y=0;
	
		
		auto move=MoveBy::create(0.1,Point(x,y));
		
		auto ani= animation::getAnimation("enermy_2.plist", "enermy_2.png", "enermy_2_", 5,heroBad3,3);
		auto action = Animate::create(ani);
		heroBad3->runAction(Sequence::create(action,move, NULL));	

		if(heroBad3->getPositionX()<0)
		{
			this->unschedule(schedule_selector(MapThere::heroBadRounf));
			this->removeChild(heroBad3,true);
			chu->setVisible(true);
		}

		this->schedule(schedule_selector(MapThere::heroBadRounf),0.1);
}


//坏人移动，实现找人移动
void MapThere::heroRound(float d)
{
	
	
	Point pp= moveBad(true,herohrea3->getPosition());
	auto move=MoveBy::create(0.1,pp);
   
    auto ani= animation::getAnimation("enermy_2.plist", "enermy_2.png", "enermy_2_", 5,heroBad3,3);
	auto action = Animate::create(ani);
	heroBad3->runAction(Sequence::create(action,move, NULL));
	if(kj==0)
	{
	   this->schedule(schedule_selector(MapThere::heroRound),0.3);
	}
	else
	{
		this->unschedule(schedule_selector(MapThere::heroRound));
	}
  
}


//坏人移动的算法
Point MapThere::moveBad(bool active,Point ph)
{
	
		auto s=heroBad3;
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
Point  MapThere::movePlayer(Point p,Point p3)
{
    int x =(p.x)/tileMap3->getTileSize().width;
    int y= tileMap3->getMapSize().height-(p.y/tileMap3->getTileSize().height);
    
    Point currentPoint=Point(x,y);    
    if (x!=tileMap3->getMapSize().width && y!=tileMap3->getMapSize().height)
    {
        
        int tilegid=_collidable3->getTileGIDAt(currentPoint);
       
		cocos2d::Value value=tileMap3->getPropertiesForGID(tilegid);
       
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









