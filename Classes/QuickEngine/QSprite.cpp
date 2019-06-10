#include "QSprite.h"

QE_SINGLETON_CPP(QSprite);

Sprite* QSprite::createBgSprite()
{
	return createBgSprite("bg.png");
}

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
