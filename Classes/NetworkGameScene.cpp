#pragma execution_character_set("utf-8")

#include "NetworkGameScene.h"

vector< Sprite*> NetworkGameScene::_onSprites;

/*
宝宝和坏人发言完毕之后可以选择是否继续发言

裁判发言完毕之后可以选择继续比拼和宣布宝宝玩家胜或者坏人玩家胜

*/

QE_SINGLETON2_CPP(NetworkGameScene);

QE_CreateSceneFromLayer_CPP(NetworkGameScene);
paths = { "fonts", "icon" };
QE_SetResourcesSearchDir;

_instance = this;

Connect::connect(Connect::Event::Dialog);

	initLabel();
	initMenu();
	initSprites();
	setOnSprites(0);
	initListView();
	initEditBox();
return true;
}

void NetworkGameScene::dealServerResponse(int statusCode)
{
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
}

void NetworkGameScene::initLabel()
{
	createLabel("坏人：");
	_label->setPosition(60, 390);
	createLabel("宝宝：");
	_label->setPosition(60, 325);
	createLabel("裁判：");
	_label->setPosition(60, 265);

	NW_InitLogLabel(150, 20);
}

void NetworkGameScene::initMenu()
{
	QE_CreateLabelMenu(840, 100, "发送", NetworkGameScene, createRoom);
	QE_CreateLabelMenuAgain(10, 500, "返回", NetworkGameScene, back);
}

void NetworkGameScene::createRoom()
{

}

void NetworkGameScene::joinRoom()
{

}

void NetworkGameScene::back() { QE_ReplaceScene(SignInScene); };

void NetworkGameScene::initEditBox()
{
	//输入ID的框
	_box = createEditBox("orange_edit.png");
	_box->setPosition(Vec2(10, 100));
	_box->setSize(Size(820, 38));
	_box->setPlaceHolder("请输入聊天信息");	//当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符
}

void NetworkGameScene::initSprites()
{
	for (int i = 0; i < 3; ++i)
	{
		float posY = 370 - 60 * i;

		Sprite* spr = Sprite::create("btn_radio_off_holo.png");
		spr->setPosition(Vec2(0, posY));
		spr->setAnchorPoint(Vec2(0, 0));
		addChild(spr);

		spr = Sprite::create("btn_radio_on_holo.png");
		spr->setPosition(Vec2(0, posY));
		spr->setAnchorPoint(Vec2(0, 0));
		addChild(spr);
		_onSprites.push_back(spr);
		
	}
}

void NetworkGameScene::setOnSprites(int index)
{
	for (size_t i = 0; i < _onSprites.size(); i++)
	{
		_onSprites[i]->setVisible(false);
	}
	_onSprites[index]->setVisible(true);
}

void NetworkGameScene::initListView()
{
	_listView = ListView::create();
	_listView->setDirection(ScrollView::Direction::BOTH);
	_listView->setBounceEnabled(true);//回弹效果
	_listView->setBackGroundImage("green_edit.png");
	_listView->setBackGroundImageScale9Enabled(true);
	_listView->setContentSize(Size(500, 360));
	_listView->setAnchorPoint(Vec2(0, 0));
	_listView->setPosition(Vec2(400, 160));
	addChild(_listView);
	for (int i = 0; i < 10; i++)
	{
		Layout* widget = Layout::create();
		widget->setContentSize(Size(240, 30));

		//创建RichText对象
		RichText* richText = RichText::create();
		//设置是否忽略用户定义的内容大小
		richText->ignoreContentAdaptWithSize(false);
		//设置内容大小
		richText->setContentSize(Size(500, 50));
		richText->setPosition(Vec2(5, 0));
		richText->setAnchorPoint(Vec2(0, 0));

		//创建文本类型的RichElement对象
		RichElementText* re1 = RichElementText::create(1, Color3B::BLUE, 255, "宝宝：", QE_Font, 20);
		RichElementText* re2 = RichElementText::create(2, Color3B::RED, 255, "  你是坏人，不搭理你。", QE_Font, 20);
		//创建图片类型的RichElement对象
		RichElementImage* re3 = RichElementImage::create(3, Color3B::WHITE, 255, "child.png");
		//创建换行RichElement对象
		RichElementNewLine* newLine = RichElementNewLine::create(77, Color3B::WHITE, 255);

		richText->pushBackElement(re1);
		//richText->pushBackElement(newLine);
		richText->pushBackElement(re3);
		richText->pushBackElement(re2);
		//richText->insertElement(newLine, 3);

		widget->addChild(richText);
		_listView->pushBackCustomItem(widget);
	}
}