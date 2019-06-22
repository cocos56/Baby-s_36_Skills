#pragma execution_character_set("utf-8")
#pragma once
#include "cocos2d.h"
#include "HRocker.h"
#include "animation.h"
USING_NS_CC; 
class MapOne :public Layer,public animation
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(MapOne);


	void  PlayerPoint(Point p);

	void RunEnd();
	void StopAnimation();
	void SetAnimation(const char* name_plist, const char* name_png, const char* name_each, unsigned int num, bool run_directon,int f);
	Animation* getAnimation(const char* name_plist, const char* name_png, const char* name_each, const unsigned int num, bool run_directon);
	void update(float f);

private:
	Sprite* _player;
    void back();
	void back1();
	void back2();
	void back3();
	void MoveMap(Point position);
	void movePlayer(Vec2 p);

	Sprite * _player1;
	Sprite * _player2;
	Sprite * _player3;
	Sprite * _player4;
	Sprite* hero;

	
};

class HrockerLayer:public Layer 
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(HrockerLayer);

};