#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine/QuickEngine.h"

class animation
{
public:

	void RunEnd();
	void StopAnimation(Sprite * hero1);
	void SetAnimation(const char* name_plist, const char* name_png, const char* name_each, unsigned int num, bool run_directon,Sprite * hero1,int f);
	Animation* getAnimation(const char* name_plist, const char* name_png, const char* name_each, const unsigned int num, Sprite * hero1,bool run_directon);
private:
	bool IsRunning;
	bool HeroDirecton;
	
};

