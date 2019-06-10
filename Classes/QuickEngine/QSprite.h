#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine.h"

/*
Quick Engine所属快速精灵模块
含：
1.QSprite类
用途：用于快速管理精灵
*/

class QSprite
{
	QE_SINGLETON_H(QSprite);

public:
	static Sprite* createBgSprite();
	static Sprite* createBgSprite(const std::string& filename);
};

#define QE_addBgSpriteToThis addChild(QSprite::createBgSprite());