#pragma execution_character_set("utf-8")

#include "HelloWorldScene.h"

QE_CreateSceneFromLayer_CPP(HelloWorld);
	_listView = ListView::create();
	testListView();
	return true;
}

void HelloWorld::testListView()
{
	_listView->setDirection(ScrollView::Direction::VERTICAL);
	_listView->setBounceEnabled(true);//回弹效果
	_listView->setBackGroundImage("green_edit.png");
	_listView->setBackGroundImageScale9Enabled(true);
	_listView->setContentSize(Size(240, 130));
	_listView->setPosition(Vec2(420, 160));
	addChild(_listView);
	for (int i = 0; i < 10; i++)
	{
		Layout* widget = Layout::create();;
		widget->setContentSize(Size(240, 50));
		auto* str = String::createWithFormat("TextArea Widget acn line wrap %d", i + 1);
		Text* text = Text::create(str->getCString(), "Marker Felt.ttf", 13);
		text->setContentSize(Size(60, 10));
		text->setPosition(Vec2(20, 25));
		text->setAnchorPoint(Vec2(0, 0));
		widget->addChild(text);
		_listView->pushBackCustomItem(widget);
	}
}

void HelloWorld::setWidget(ListView* _listView, std::string str)
{
	_listView->removeAllChildren();
	std::string temp = "";
	int index = 0, max = str.length(), times=0;
	while (true)
	{
		temp = str.substr(0, max);
		CCLOG("temp=%s", temp.c_str());
		Layout* widget = Layout::create();
		widget->setContentSize(Size(240, 50));
		Text* text = Text::create(temp.c_str(), "Marker Felt.ttf", 13);
		text->setContentSize(Size(60, 10));
		text->setPosition(Vec2(20, 25));
		text->setAnchorPoint(Vec2(0, 0));
		widget->addChild(text);
		_listView->pushBackCustomItem(widget);
		if (times <= 10)
		{
			times++;
		}
		else
		{
			break;
		}
	}
}