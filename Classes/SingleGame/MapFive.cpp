#include "MapFive.h"

#include "HRocker.h"
#include "Battle.h"




TMXTiledMap *tileMap5;
HRocker* rocker5;
TMXLayer  *_collidable5;



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

	k1=0;
	kj=0;
	j=0;

	 tileMap5 = TMXTiledMap::create("school.tmx");
	tileMap5->setAnchorPoint(Vec2::ZERO);
	tileMap5->setPosition(Vec2::ZERO);
	this->addChild(tileMap5);
	
	UserDefault::getInstance()->setIntegerForKey("level",4);

	_collidable5=tileMap5->getLayer("peng4");
	_collidable5->setVisible(false);

	 chu=Sprite::create("enter.png");
	chu->setPosition(930,100);
	chu->setVisible(false);
	this->addChild(chu);


	auto object=tileMap5->getObjectGroup("people4");
	ValueMap map3=object->getObject("hero4");
	int x3=map3.at("x").asInt();
	int y3=map3.at("y").asInt();

	 herohrea5=Sprite::create("buddy_1_1.png");
	herohrea5->setPosition(x3,y3);
	tileMap5->addChild(herohrea5,1);


	ValueMap map4=object->getObject("herbad4");
	int x4=map4.at("x").asInt();
	int y4=map4.at("y").asInt();

	heroBad5=Sprite::create("enermy_4_1.png");
	heroBad5->setPosition(x4,y4);
	tileMap5 ->addChild(heroBad5,1);
	
	this->scheduleUpdate();


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







void MapFive::update(float f)
{
	if(kj==0)
	{
		if (herohrea5->getPosition().x >heroBad5->getPosition().x) {
				if(heroBad5->isFlippedX() == true)
					heroBad5->setFlippedX(false);
			}else{
				if(heroBad5->isFlippedX() == false)
					heroBad5->setFlippedX(true);
			}
	}

	
	switch (rocker5->rocketDirection)
		{
			case 1:

				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_",5, rocker5->rocketRun,herohrea5,1);
				
				
				 p2= movePlayer(Vec2( herohrea5->getPosition().x +2, herohrea5->getPosition().y),herohrea5->getPosition());
		        herohrea5->setPosition(p2);
				
				break;
			case  2:
				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_", 5, rocker5->rocketRun,herohrea5, 2);
				 p2= movePlayer(Vec2(herohrea5->getPosition().x,herohrea5->getPosition().y +2),herohrea5->getPosition());
		        herohrea5->setPosition(p2);
				
				break;
			case 3:
				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_", 5, rocker5->rocketRun,herohrea5,3);
			
	            p2= movePlayer(Vec2( herohrea5->getPosition().x -2,  herohrea5->getPosition().y),herohrea5->getPosition());
		        herohrea5->setPosition(p2);
				
				break;
			case 4:
				animation::SetAnimation("buddy_1.plist", "buddy_1.png", "buddy_1_", 5, rocker5->rocketRun,herohrea5,4);
		    
				 p2= movePlayer(Vec2( herohrea5->getPosition().x,  herohrea5->getPosition().y -2),herohrea5->getPosition());
		        herohrea5->setPosition(p2);
				
				
				break;
			default:
				animation::StopAnimation( herohrea5);//停止所有动画和运动  
				break;
		}

	auto rectA=herohrea5->getBoundingBox();
	auto rectB=heroBad5->getBoundingBox();
	auto rectC=chu->getBoundingBox();
	
	//kj是记录碰撞
	if (rectA.intersectsRect(rectB)&&kj==0)
	{
	    animation::StopAnimation(heroBad5);
		heroBad5->stopAllActions();
		this->unschedule(schedule_selector(MapFive::heroRound));

		//DelayTime::create(3);
		


		auto scens =Battle::createScene();
		Director::getInstance()->pushScene(scens);

		kj=1;

	}

		if (rectA.intersectsRect(rectC)&&chu->isVisible())
	{
		backFive();
	}
	
	float w=pow(abs((herohrea5->getPositionX()-heroBad5->getPositionX())),2.0);
	float y=pow(abs((herohrea5->getPositionY()-heroBad5->getPositionY())),2.0);
	
	float s=sqrt( w+ y);
	
	if(s <=190&&s>=0&&k1==0&&kj==0)
	{
		   heroRound(0.1);
	
           k1=1;
	}

	
	if(kj==1)
	{
	    rocker5->resumeState();
		heroBadRounf(0.1);	
		kj=-1;
	
	}

}

void MapFive::backFive()
{
	
	this->unschedule(schedule_selector(MapFive::heroRound));
	this->unschedule(schedule_selector(MapFive::heroBadRounf));
	rocker5->stopRocker();
    Director::getInstance()->popScene();

	
}

//实现角色奔跑
void MapFive::heroBadRounf(float d)
{

	
		 if(heroBad5->isFlippedX() == true)
		 {		heroBad5->setFlippedX(false);}


		if(heroBad5->isFlippedX() == false)
		{		heroBad5->setFlippedX(true);}

	    x=-40;
	    y=0;
	
		
		auto move=MoveBy::create(0.1,Point(x,y));
		
		auto ani= animation::getAnimation("enermy_4.plist", "enermy_4.png", "enermy_4_", 5,heroBad5,3);
		auto action = Animate::create(ani);
		heroBad5->runAction(Sequence::create(action,move, NULL));	

		if(heroBad5->getPositionX()<0)
		{
			this->unschedule(schedule_selector(MapFive::heroBadRounf));
			this->removeChild(heroBad5,true);
			chu->setVisible(true);
		}

		this->schedule(schedule_selector(MapFive::heroBadRounf),0.1);
}


//坏人移动，实现找人移动
void MapFive::heroRound(float d)
{
	
	
	Point pp= moveBad(true,herohrea5->getPosition());
	auto move=MoveBy::create(0.1,pp);
   
    auto ani= animation::getAnimation("enermy_4.plist", "enermy_4.png", "enermy_4_", 5,heroBad5,3);
	auto action = Animate::create(ani);
	heroBad5->runAction(Sequence::create(action,move, NULL));
	if(kj==0)
	{
	   this->schedule(schedule_selector(MapFive::heroRound),0.3);
	}
	else
	{
		this->unschedule(schedule_selector(MapFive::heroRound));
	}
  
}


//坏人移动的算法
Point MapFive::moveBad(bool active,Point ph)
{
	
		auto s=heroBad5;
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
Point  MapFive::movePlayer(Point p,Point p3)
{
    int x =(p.x)/tileMap5->getTileSize().width;
    int y= tileMap5->getMapSize().height-(p.y/tileMap5->getTileSize().height);
    
    Point currentPoint=Point(x,y);    
    if (x!=tileMap5->getMapSize().width && y!=tileMap5->getMapSize().height)
    {
        
        int tilegid=_collidable5->getTileGIDAt(currentPoint);
       
        Value value=tileMap5->getPropertiesForGID(tilegid);
       
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