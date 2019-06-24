#pragma once
#include "cocos2d.h"
#include"animation.h"
USING_NS_CC;
class MapFive :public Layer,public animation
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(MapFive);
	void backFive();
private:
	Sprite* hero;


	bool HeroDirecton5;
	
	void update(float f);
	void PlayerPoint(Point p);
	void heroRound(float d);
	Point  movePlayer(Point p,Point p3);
	
   Point moveBad(bool s,Point ph);
   void heroBadRounf(float d);
   Sprite *chu;

   int k1;
   int kj;
   int j;


	Sprite * herohrea5;

	static Layer * layer;
	Point  p2;
	Sprite * heroBad5;
	float y;
	float x;



};
class HrockerLayer5:public Layer
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(HrockerLayer5);

};

