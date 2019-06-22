#pragma execution_character_set("utf-8")
#include "Battre.h"
#include "MapTwo.h"
#include<string.h>

#include "DataParse.h"

Scene * Battre::createScene()
{
	Scene* scene = Scene::create();
	Layer * layer =Battre::create();
	scene->addChild(layer);
	return scene;
}
bool Battre::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Size size=Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	button=Button::create("CloseNormal.png","CloseNormal.png");
	button->setPosition(Vec2(150,50));
	button->addClickEventListener(CC_CALLBACK_1(Battre::falseTextTurn,this));
	this->addChild(button);


	 button1=Button::create("CloseNormal.png","CloseNormal.png");
	button1->setPosition(Vec2(size.width-150,50));
	button1->addClickEventListener(CC_CALLBACK_1(Battre::tureTextTurn,this));
	this->addChild(button1);

	dic=DataParse::getChapter(1);
	auto str=(String *)(dic->objectForKey("level_1_star"));
    
  
	label2 = Label::create();
	label2->setPosition(visibleSize.width / 5, visibleSize.height / 4);
	label2->setTag(1);
	this->addChild(label2,2);
	Lable_Set(label2,str,3);
	
	return true;
}

void Battre::backScese()
{
	Director::getInstance()->popScene();
}

void Battre::Lable_Set(Label *label1 ,String* str,int i)
{
	content = *str;
	
	n = 0;// 0~3来获得一个中文字符
	
	label=nullptr;

	label = label1;

	label->setString("");
	label->setSystemFontSize(40);
	label->setTextColor(Color4B(255,255,255,100));

	label->setAnchorPoint(Vec2(0, 1));//设置锚点，从左向右打印
	label->setDimensions(600, 200);

	this->schedule(schedule_selector(Battre::showFont),0.2);
}






void Battre::showFont(float dt) {

	std::string c=content.getCString();

	n = n + 3;
	std::string str = c.substr(0, n);

	CCLOG("len=%d, n=%d", c.length(), n);
	CCLOG("str=%s", str.c_str());

	label->setString(str);
	button->setEnabled(false);
	button1->setEnabled(false);
	
	if (n > content.length()) {
		this->unschedule(schedule_selector(Battre::showFont));
		button->setEnabled(true);
		button1->setEnabled(true);
		n=0;
		content="";
	}
}

void Battre::falseTextTurn(Ref *sender)
{
	
	 dic=Dictionary::createWithContentsOfFile("text.xml");
	auto str=(String *)(dic->objectForKey("play3"));
	
	Lable_Set(label2,str,3);
}


 void Battre::tureTextTurn(Ref *sender)
 {
	 
	 dic=Dictionary::createWithContentsOfFile("text.xml");
	auto str=(String *)(dic->objectForKey("play4"));
	log("sdajjdsaj");

	Lable_Set(label2,str,3);
 }

