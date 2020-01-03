#pragma execution_character_set("utf-8")

#include "QAnimate.h"

int QAnimate::num;

void QAnimate::initFramsNumFromPlistFile(const string& fileName)
{
	Dictionary* dic = Dictionary::createWithContentsOfFile((fileName + ".plist").c_str());
	Dictionary * frameDic = (Dictionary*)dic->objectForKey("frames");
	num = frameDic->allKeys()->count();
	frameDic->release();
}

void QAnimate::initAnimateFromPlistFile(Animate*& animate, Sprite*& sprite, int x, int y, const string& fileName, string dirName, float scale, bool isRestoreOriginalFrame)
{
	initFramsNumFromPlistFile(fileName);
	Animation* animation = Animation::create();
	string fn;
	sprite = Sprite::create();
	sprite->setPosition(x, y);
	sprite->setAnchorPoint(Vec2(0, 0));
	for (int i = 1; i <= num; i++)
	{
		fn = dirName + fileName + "/" + fileName + to_string(i) + ".png";
		animation->addSpriteFrameWithFile(fn);
	}
	animation->setDelayPerUnit(1);
	animation->setRestoreOriginalFrame(isRestoreOriginalFrame);
	animate = Animate::create(animation);
}

void QAnimate::createFramsPlayerFromPlistFile(const string& fileName, vector<Sprite*>& sprites, int x, int y, Layer* layer, string dirName, float scale)
{
	initFramsNumFromPlistFile(fileName);
	Sprite* s;
	string fn;
	for (int i = 1; i <= num; i++)
	{
		fn = dirName + fileName + "/" + fileName + to_string(i) + ".png";
		s = Sprite::create(fn);
		s->setPosition(x, y);
		s->setScale(scale);
		s->setAnchorPoint(Vec2(0, 0));
		layer->addChild(s);
		sprites.push_back(s);
	}
	playFramFromFrams(sprites);
}

void QAnimate::playFramFromFrams(vector<Sprite*>& frames, int num)
{
	if (num <= 0)
	{
		for (size_t i = 0, length = frames.size(); i < length; i++)
		{
			frames.at(i)->setVisible(false);
		}
		return;
	}
	else if (num >= frames.size())
	{
		num = frames.size();
	}
	//从逻辑序号转成物理序号
	num--;
	for (size_t i = 0, length=frames.size(); i < length; i++)
	{
		if (i != num)
			frames.at(i)->setVisible(false);
		else
			frames.at(i)->setVisible(true);
	}
}