﻿#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class MapTwo :public Layer,public animation
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(MapTwo);
	void backTwo();
	void update(float f);
	void PlayerPoint(Point p);
	void heroRound(float d);
	Point  movePlayer(Point p,Point p3);
	
	Point moveBad(bool s,Point ph);
	void heroBadRounf(float d);
	
	int count ,k1, kj, j;

private:
	Sprite *herohrea;
	bool HeroDirecton;
	static Layer *layer;
	Point  p2;
	Sprite *heroBad;
	float y;
	float x;
	Sprite *chu;
};

class HrockerLayer2:public Layer
{
public:
	static Scene *createScene();
    virtual bool init();
	CREATE_FUNC(HrockerLayer2);
};
