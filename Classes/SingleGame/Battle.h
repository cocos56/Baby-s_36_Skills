#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class Battle :public Layer
{
public:
	static Scene * createScene();
    virtual bool init();
	CREATE_FUNC(Battle);

	
	void Lable_Set(Label *label1 ,String* str,int i);
	void showFont(float dt);
	void falseTextTurn(Ref *sender);
	void tureTextTurn(Ref *sender);
	void update(float f);
	void judeRight();
	void returnScene();
	 void returnScene(float f);

private:
    String content;
	int n ;
	Label *label;
	Label *label2;
	Dictionary *dic;
	Button *button;
	Button *button1;
	Size visibleSize;
	int Level;
	char Levels[20];
	int I;
	int right;
	int  LevelI;

	Size  size;
	Sprite *bg1;
	Sprite *bg2;
	Sprite *bg3;
	Sprite *bg4;
};
