#pragma execution_character_set("utf-8")

#include "Battle.h"
 
int z=0;
 Layer * layerLose;

Scene * Battle::createScene()
{
	Scene *scene = Scene::create();
	Layer *layer =Battle::create();
	scene->addChild(layer);
	return scene;
}

bool Battle::init()
{
	if (!Layer::init()){ return false; }
	
	UserDefault::getInstance()->setIntegerForKey("i",1);
	UserDefault::getInstance()->setIntegerForKey("True",-1);
	UserDefault::getInstance()->setIntegerForKey("end",-1);
	UserDefault::getInstance()->setIntegerForKey("ok",1);

	visibleSize = Director::getInstance()->getVisibleSize();
	size=Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景
	auto bg=Sprite::create("bghuang.png");
	auto scaleX = size.width/bg->getContentSize().width;
	auto scaleY = size.height/bg->getContentSize().height;
	bg->setScale(scaleX,scaleY);
	bg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(bg,0);

	//坏蛋赢图
	bg1=Sprite::create("2123.png");
	bg1->setPosition(Vec2(487,437));
	bg1->setVisible(false);
	this->addChild(bg1,1);

	//玩家赢图
	bg2=Sprite::create("124.png");
	bg2->setPosition(Vec2(477,426));
	bg2->setVisible(false);
	this->addChild(bg2,1);

	//tu
	auto bg5=Sprite::create("solo2.png");
	bg5->setPosition(Vec2(473,153));
	this->addChild(bg5,3);

	//闭合图1
	bg3=Sprite::create("left.png");
	bg3->setPosition(Vec2(304,323));
	this->addChild(bg3,2);

	//闭合图2
	bg4=Sprite::create("right.png");
	bg4->setPosition(Vec2(603,323));
	this->addChild(bg4,2);

	 Level=UserDefault::getInstance()->getIntegerForKey("level");
	 I=UserDefault::getInstance()->getIntegerForKey("i");

	 right=-1;
	 LevelI=Level*10+I;

	button=Button::create("Ybutton.png","Ybutton1.png");
	button->setPosition(Vec2(69,153));
	button->addClickEventListener(CC_CALLBACK_1(Battle::falseTextTurn,this));
	button->setTag(4);
	this->addChild(button,3);

	button1=Button::create("Nbutton.png","Nbutton1.png");
	button1->setPosition(Vec2(885,153));
	button1->addClickEventListener(CC_CALLBACK_1(Battle::tureTextTurn,this));
	button1->setTag(3);
	this->addChild(button1,3);

	auto dic=DataParse::getChapter(Level);
	sprintf(Levels,"level_%d_word",LevelI);
	auto str=(String *)(dic->objectForKey(Levels));
  
	label2 = Label::create();
	label2->setPosition(visibleSize.width / 5, visibleSize.height / 2.5);
	label2->setTag(1);
	this->addChild(label2,3);
	Lable_Set(label2,str,3);

	this->scheduleUpdate();
	return true;
}


void Battle::update(float f)
{
	 I=UserDefault::getInstance()->getIntegerForKey("i");
	
	 //计算超过六条结束游戏
	 if(I==7)
	 {
		 this->unschedule(schedule_selector( Battle::showFont));
		 Director::getInstance()->popScene();
		 return ;
	 }
	 
	 
	 //正确答案
	int result=DataParse::getNum(LevelI);
	//玩家答案
	int retult2=UserDefault::getInstance()->getIntegerForKey("True");

	
	//答案为0时，答对
	if(result==retult2&&result==0) { right=0; }
	//答案为1时，答对
	else if(result==retult2&&result==1) { right=1; }
	//答案不对，玩家给为1
	else if(result!=retult2&&retult2==1){ right=3; }
	//答案不对，玩家给为0
	else if(result!=retult2&&retult2==0){ right=3; }

	//答对了答案
	if(right==0){
		bg1->setVisible(true);
		
		UserDefault::getInstance()->setIntegerForKey("True",-1);
		UserDefault::getInstance()->setIntegerForKey("i",I+1);
		
		Level=UserDefault::getInstance()->getIntegerForKey("level");
		auto dic=DataParse::getChapter(Level);
		I=UserDefault::getInstance()->getIntegerForKey("i");
		if(I==7){ I-=1; }
		LevelI=Level*10+I;
		sprintf(Levels,"level_%d_word",LevelI);
		  
		right=-1;
		
		auto str=(String *)(dic->objectForKey(Levels));
	
		Lable_Set(label2,str,3);
	}

	//答对了答案，答案为1
	 else if(right==1){
		  bg1->setVisible(true);
		  UserDefault::getInstance()->setIntegerForKey("True",-1);
		  UserDefault::getInstance()->setIntegerForKey("i",I+1);
		  
		  Level=UserDefault::getInstance()->getIntegerForKey("level");
		  auto dic=DataParse::getChapter(Level);
		  I=UserDefault::getInstance()->getIntegerForKey("i");
		  if(I==7){ I=I-1; }
		  LevelI=Level*10+I;
		  sprintf(Levels,"level_%d_word",LevelI);
		  
		  auto str=(String *)(dic->objectForKey(Levels));
		  right=-1;
		  
		  Lable_Set(label2,str,3);
		  log("1->%s",Levels);
	 }

	//答错了
	 else if(right==3){
		bg2->setVisible(true);
		UserDefault::getInstance()->setIntegerForKey("True",-1);
		
		right=-1;
		//ok记得是错误
		UserDefault::getInstance()->setIntegerForKey("ok",0);
		Level=UserDefault::getInstance()->getIntegerForKey("level");
		auto dic=DataParse::getChapter(Level);
		I=UserDefault::getInstance()->getIntegerForKey("i");
		if(I==7){ I=I-1; }
		LevelI=Level*10+I;
		sprintf(Levels,"level_%d_word",LevelI);
		auto str=(String *)(dic->objectForKey(Levels));
		
		Lable_Set(label2,str,3);
	 }
 }

 void Battle::returnScene(float f)
 {
	 Director::getInstance()->popScene();
 }


void Battle::Lable_Set(Label *label1 ,String* str,int i)
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

	this->schedule(schedule_selector(Battle::showFont),0.2);
}


void Battle::judeRight()
{
	auto move=MoveTo::create(0.1, Vec2( bg3->getPosition().x+500,bg3->getPosition().y));
	auto move1=MoveTo::create(0.1,Vec2( bg4->getPosition().x-500,bg4->getPosition().y));

	bg3->runAction(move);
	bg4->runAction(move1);
}


void Battle::showFont(float dt) {
	string c=content.getCString();

	n = n + 3;
	
	string str = c.substr(0, n);

	label->setString(str);
	
	if(n > content.length())
	{
		this->unschedule(schedule_selector(Battle::showFont));
		if(UserDefault::getInstance()->getIntegerForKey("ok")==0)
		{
			Director::getInstance()->popScene();
		}
		n=0;
		content="";
		
	    if(bg1->isVisible()){
			 bg1->setVisible(false);
			 judeRight();
		 }
		
		if(bg2->isVisible()){
			 bg2->setVisible(false);
			 judeRight();
		 }

		button->setEnabled(true);
		button1->setEnabled(true);
	}
}

void Battle::falseTextTurn(Ref *sender)
{
	UserDefault::getInstance()->setIntegerForKey("True",0);
	button->setEnabled(false);
	button1->setEnabled(false);

	//但点击按钮时，公布答案
	auto move=MoveTo::create(0.1, Vec2(bg3->getPosition().x -500,bg3->getPosition().y));
	auto move1=MoveTo::create(0.1, Vec2(bg4->getPosition().x +500,bg4->getPosition().y));
	bg3->runAction(move);
	bg4->runAction(move1);
}


 void Battle::tureTextTurn(Ref *sender)
 {	
	UserDefault::getInstance()->setIntegerForKey("True",1);
	button->setEnabled(false);
	button1->setEnabled(false);
	auto move=MoveTo::create(0.1, Vec2(bg3->getPosition().x -500,bg3->getPosition().y));
	auto move1=MoveTo::create(0.1, Vec2(bg4->getPosition().x +500,bg4->getPosition().y));
	bg3->runAction(move);
	bg4->runAction(move1);
 }

