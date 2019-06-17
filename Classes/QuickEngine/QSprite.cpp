#pragma execution_character_set("utf-8")

#include "QSprite.h"

Sprite* QSprite::createBgSprite(){return createBgSprite("bg.png");}

Sprite* QSprite::createBgSprite(const std::string& filename)
{
	//获取窗口大小
	Size size = Director::getInstance()->getWinSize();
	//创建背景精灵
	Sprite* bg = Sprite::create(filename);
	//做适配
	float scaleX = size.width / bg->getContentSize().width;
	float scaleY = size.height / bg->getContentSize().height;
	bg->setScale(scaleX, scaleY);
	//设置位置
	bg->setPosition(Vec2(size.width / 2, size.height / 2));
	return bg;
}

Sprite* QSprite::create(string fileName, int x, int y)
{
	Sprite* spr = Sprite::create(fileName);
	spr->setAnchorPoint(Vec2(0, 0));
	spr->setPosition(x, y);
	return spr;
}