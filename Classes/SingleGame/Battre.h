#pragma execution_character_set("utf-8")
#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "ui/CocosGUI.h"
using namespace ui;

class Battre :public Layer
{
public:
	 static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(Battre);

	void backScese();
	void Lable_Set(Label *label1 ,String* str,int i);
	void showFont(float dt);
	void falseTextTurn(Ref *sender);
	 void tureTextTurn(Ref *sender);

private:
    String content;
	int n ;
	Label* label;
	Label *label2;
	Dictionary *dic;
	ui::Button * button;
	ui::Button *button1;
	Size visibleSize;
};

