#pragma once

/*
Quick Engine所属快速精灵模块
含：
1.QSprite类
用途：用于快速管理精灵
*/


#include "QE.h"

class QSprite
{
	QE_SINGLETON_H(QSprite);

public:
	static Sprite* createBgSprite();
	static Sprite* createBgSprite(const std::string& filename);
};

#define QE_addBgSpriteToThis addChild(QSprite::createBgSprite());