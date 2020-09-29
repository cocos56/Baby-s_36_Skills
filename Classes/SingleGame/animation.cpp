#pragma execution_character_set("utf-8")

#include "animation.h"

void animation::StopAnimation( Sprite * hero1)
{
	if (!IsRunning){ return; }
	
	hero1->stopAllActions();
	IsRunning = false;
}


void animation::SetAnimation(const char* name_plist, const char* name_png, const char* name_each, unsigned int num, bool run_directon,Sprite * hero1,int i)
{
	if (HeroDirecton != run_directon)
	{
		HeroDirecton = run_directon;
		hero1->setFlippedX(run_directon);  
	}

	if (IsRunning){ return; }

	auto ani = getAnimation(name_plist, name_png, name_each, num, hero1,run_directon);
	auto action = Animate::create(ani);
	
	auto ccback = CallFunc::create(CC_CALLBACK_0(animation::RunEnd, this));
	auto act = Sequence::create(action,ccback, NULL);
	hero1->runAction(act);

	IsRunning = true;
}

void animation::RunEnd()
{
	IsRunning = false;
}

Animation* animation::getAnimation(const char* name_plist, const char* name_png, const char* name_each, const unsigned int num,Sprite * hero1, bool run_directon)
{
		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile(name_plist, name_png);
		hero1->setTexture(String::createWithFormat("%s1.png", name_each)->getCString());
		auto spriteBatch = SpriteBatchNode::create(name_png);
		//addChild(spriteBatch);
		Vector<SpriteFrame*> animFrames(num);
		for (int i = 1; i < num; i++)
		{
			auto frame = cache->getSpriteFrameByName(String::createWithFormat("%s%d.png", name_each, i)->getCString());
			animFrames.pushBack(frame);
		}
	    auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
		return animation;
}
