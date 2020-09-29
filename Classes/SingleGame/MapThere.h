#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class MapThere :public Layer,public animation
{
public:
	static Scene *createScene();
    virtual bool init();
	CREATE_FUNC(MapThere);
	void backThere();

	bool HeroDirecton3;
	
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

private:
	Sprite *herohrea3;

	static Layer *layer;
	Point  p2;
	Sprite *heroBad3;
	float y;
	float x;
};

class HrockerLayer3:public Layer
{
public:
	static Scene *createScene();
    virtual bool init();
	CREATE_FUNC(HrockerLayer3);
};

