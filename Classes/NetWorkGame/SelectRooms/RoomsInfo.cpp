#pragma execution_character_set("utf-8")

#include "RoomsInfo.h"

Label* RoomsInfo::_label;
Button* RoomsInfo::_btn;
int RoomsInfo::_roomNum = 0;
vector<Label*> RoomsInfo::_roomsName, RoomsInfo::_roomsCreator;

ScrollView* RoomsInfo::initScrollView(Node* target){
	_roomsName.clear();
	_roomsCreator.clear();
	_roomNum = 0;

	Size cSize = Size(800, 411);
	Vec2 position = Vec2(80, 240);

	//Scale9Sprite* s = Scale9Sprite::create("roomcardbg.png");  //设置ScrollView背景，便于查看容器大小
	//s->setContentSize(cSize + Size(10, 10));
	//s->setPosition(position-Vec2(5,5));
	//s->setAnchorPoint(Vec2(0, 0));
	//target->addChild(s);


	ScrollView* _scrollView = ScrollView::create();
	_scrollView->setContentSize(cSize);//因为图片的高度为215
	_scrollView->setAnchorPoint(Vec2(0, 0));
	_scrollView->setPosition(position);
	_scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	_scrollView->setBounceEnabled(true);
	_scrollView->setInnerContainerSize(Size(260 * 9, 260));
	target->addChild(_scrollView);

	//因为图片的高度为215,135=图片的宽度120+缝隙15
	_scrollView->addEventListener(bind(&RoomsInfo::scrollViewSdidScroll, placeholders::_1, placeholders::_2));
	for (int i = 0; i < 9; i++)
	{
		_btn = Button::create("roomcard.png", "roomcard.png");
		_btn->setScale9Enabled(true);
		_btn->setContentSize(Size(244, 260));
		_btn->setPosition(Vec2(260 * i + 120, 130));// 215/2=107.5，75=120/2+15，加70是为了让左右边界处都留有缝隙
		_btn->addTouchEventListener(bind(&RoomsInfo::selectScene, placeholders::_1, placeholders::_2));
		_btn->setTag(i + 1);

		createLabel("null", 120, 150);
		_roomsName.push_back(_label);
		createLabel("null", 120, 100);
		_roomsCreator.push_back(_label);
		createLabel("点此查看", 70, 40);
		_label->setColor(Color3B::WHITE);

		_scrollView->addChild(_btn);
	}
	return _scrollView;
}

void RoomsInfo::setRoomInfo(string name, string creator){
	_roomsName.at(_roomNum)->setString(name);
	_roomsCreator.at(_roomNum++)->setString(creator);
}

Label* RoomsInfo::createLabel(string str, int x, int y){
	_label = Label::create(str, QE_Font, 24);
	_label->setAnchorPoint(Vec2(0, 0));
	_label->setPosition(x, y);
	_label->setColor(Color3B::BLACK);
	_btn->addChild(_label);
	return _label;
}

//scrollView滑动选项
void RoomsInfo::scrollViewSdidScroll(Ref* sender, ScrollView::EventType type){
	switch (type){
		case ScrollView::EventType::SCROLL_TO_TOP:{
			CCLOG("滑倒顶部了！");
			break;
		}
		case ScrollView::EventType::SCROLL_TO_BOTTOM:{
			CCLOG("滑倒底部了！");
			break;
		}
		case ScrollView::EventType::SCROLL_TO_LEFT:{
			CCLOG("滑倒左边了！");
			break;
		}
		case ScrollView::EventType::SCROLL_TO_RIGHT:{
			CCLOG("滑倒右边了！");
			break;
		}
		case ScrollView::EventType::SCROLLING:{
			CCLOG("正在滑动中！");
			break;
		}
		case ScrollView::EventType::BOUNCE_BOTTOM:{
			CCLOG("回弹到底部了！");
			break;
		}
		case ScrollView::EventType::BOUNCE_LEFT:{
			CCLOG("回弹到左边了！");
			break;
		}
		case ScrollView::EventType::BOUNCE_TOP:{
			CCLOG("回弹到顶部了！");
			break;
		}
		case ScrollView::EventType::BOUNCE_RIGHT:{
			CCLOG("回弹到右边了！");
			break;
		}
	}
}

void RoomsInfo::selectScene(Ref* sender, Widget::TouchEventType type){
	if (type != Widget::TouchEventType::ENDED){ return; }
	_btn = (Button*)sender;
	string text = "您选择了房间：" +_roomsName.at(_btn->getTag()-1)->getString() + "\n";
	if (_roomNum < _btn->getTag()) { text += "但该房间不可选择。\n原因：该房间未创建"; }
	else{ text += "此房间可选择。"; }
	QMessageBox(text);
}