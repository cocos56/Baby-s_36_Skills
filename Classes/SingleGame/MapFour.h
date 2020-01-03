#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"


class MapFour :public Layer,public animation
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(MapFour);
	void backFour();

	Sprite* hero;
	bool HeroDirecton4;
	
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
	Sprite * herohrea4;

	static Layer * layer;
	Point  p2;
	Sprite * heroBad4;
	float y;
	float x;
};
class HrockerLayer4:public Layer
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(HrockerLayer4);

};

