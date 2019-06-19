#pragma execution_character_set("utf-8")

#include "NetworkGameScene.h"

vector< Sprite*> NetworkGameScene::_onSprites;

/*

进入房间之后还要等待所有玩家全部就绪后才能开始游戏

宝宝和坏人发言完毕之后可以选择是否继续发言

裁判发言完毕之后可以选择继续比拼和宣布宝宝玩家胜或者坏人玩家胜

*/

QE_SINGLETON2_CPP(NetworkGameScene);

QE_CreateSceneFromLayer_CPP(NetworkGameScene);
	paths = { "fonts", "NetworkGameScene", "icon" };
	QE_SetResourcesSearchDir;
	//QE_addBgSprite;

	_instance = this;

	Connect::connect(Connect::Event::Dialog);

	initSprits();
	initLabel();
	initMenu();
	setOnSprites(0);
	initListView();
	initEditBox();
return true;
}

void NetworkGameScene::dealServerResponse(int statusCode)
{
	//string status = Connect::getStatus(statusCode);
	//dealServerResponse(status);
}

void NetworkGameScene::initLabel()
{
	//createLabel("坏人：");
	//_label->setPosition(60, 390);
	//createLabel("宝宝：");
	//_label->setPosition(60, 325);
	//createLabel("裁判：");
	//_label->setPosition(60, 265);

	//NW_InitLogLabel(150, 20);
}

void NetworkGameScene::initMenu()
{
	QE_CreateSpriteMenu(40, 520, "back.png", NetworkGameScene, back);
	QE_CreateSpriteMenu2(860, 20, "send.png", "sendPressed.png", NetworkGameScene, send);
}

void NetworkGameScene::send()
{

}

void NetworkGameScene::back() { QE_ReplaceScene(NetworkGameOverScene); };

void NetworkGameScene::initEditBox()
{
	Sprite* spr = Sprite::create("editBox.png");
	//输入ID的框
	_box = createEditBox("editBox.png", "editBoxPressed.png");
	_box->setPosition(Vec2(53, 20));
	_box->setSize(spr->getContentSize());
}

void NetworkGameScene::initSprits()
{
	QE_addBgSprite;
	for (int i = 0; i < 3; ++i)
	{
		float posY = 370 - 60 * i;

		Sprite* spr = Sprite::create("btn_radio_off_holo.png");
		spr->setPosition(Vec2(0, posY));
		spr->setAnchorPoint(Vec2(0, 0));
		//addChild(spr);

		spr = Sprite::create("btn_radio_on_holo.png");
		spr->setPosition(Vec2(0, posY));
		spr->setAnchorPoint(Vec2(0, 0));
		//addChild(spr);
		_onSprites.push_back(spr);
	}
}

void NetworkGameScene::setOnSprites(int index)
{
	//for (size_t i = 0; i < _onSprites.size(); i++)
	//{
	//	_onSprites[i]->setVisible(false);
	//}
	//_onSprites[index]->setVisible(true);
}

void NetworkGameScene::initListView()
{
	Sprite* spr = Sprite::create("chatBg.png");
	_listView = ListView::create();
	_listView->setDirection(ScrollView::Direction::BOTH);
	_listView->setBounceEnabled(true);//回弹效果
	_listView->setBackGroundImage("chatBg.png");
	_listView->setBackGroundImageScale9Enabled(true);
	_listView->setContentSize(spr->getContentSize());
	_listView->setAnchorPoint(Vec2(0, 0));
	_listView->setPosition(Vec2(350, 110));
	addChild(_listView);
	addListViewElement("小朋友，给你一根棒棒糖可以跟我走嘛？", "scoundrelPP.png");
	addListViewElement("你是坏人，不可以跟你走。", "childPP.png");
	addListViewElement("本局宝宝胜。", "refereePP.png");
}

void NetworkGameScene::addListViewElement(const string msg, const string pic)
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

	RichElementText* re2 = RichElementText::create(2, Color3B::RED, 255," : " + msg, QE_Font, 20);
	RichElementImage* re3 = RichElementImage::create(3, Color3B::WHITE, 255, pic);
	richText->pushBackElement(re3);
	richText->pushBackElement(re2);

	widget->addChild(richText);
	_listView->pushBackCustomItem(widget);
}