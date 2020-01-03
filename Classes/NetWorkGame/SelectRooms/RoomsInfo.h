#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class RoomsInfo
{
public:
	static ScrollView* initScrollView(Node* target);
	static void setRoomInfo(string name, string creator);
private:
	static Label* createLabel(string str, int x, int y);
	static Label* _label;
	static vector<Label*> _roomsName, _roomsCreator;
	static Button* _btn;
	static int _roomNum;
	static void scrollViewSdidScroll(Ref* sender, ScrollView::EventType type);
	static void selectScene(Ref* sender, Widget::TouchEventType type);
};