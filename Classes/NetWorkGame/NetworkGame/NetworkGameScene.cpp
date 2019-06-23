#pragma execution_character_set("utf-8")

#include "NetworkGameScene.h"

vector< Sprite*> NetworkGameScene::_onSprites;
Sprite* NetworkGameScene::_spr, * NetworkGameScene::_confirmSpr, * NetworkGameScene::_judgeSpr;
Menu* NetworkGameScene::_menu, * NetworkGameScene::_sendMenu;
EditBox* NetworkGameScene::_msgBox;

/*
进入房间之后还要等待所有玩家全部就绪后才能开始游戏
宝宝和坏人发言完毕之后可以选择是否继续发言
裁判发言完毕之后可以选择继续比拼和宣布宝宝玩家胜或者坏人玩家胜
*/

QE_SINGLETON2_CPP(NetworkGameScene);

QE_CreateSceneFromLayer_CPP(NetworkGameScene);
	paths = { "fonts", "NetworkGameScene", "icon" }; 
	QE_SetResourcesSearchDir;

	_instance = this;

	initSprits();
	initLabel();
	initMenu();
	initListView();
	initEditBox();
	initConfrimSprite();
	myTurn();
	return true;
}

void NetworkGameScene::dealServerResponse(int statusCode){
	if (Connect::_nowEvent == 8) {return;}
	if (statusCode == 921){
		_instance->setOnSprite(0);
		if (SelectRoleScene::_index == 3) { _instance->myTurn(true); }
		else { _instance->myTurn(); }
	}
	else if(statusCode == 931) {
		_instance->setOnSprite(1);
		if (SelectRoleScene::_index == 1) { _instance->myTurn(true); }
		else { _instance->myTurn(); }
	}
	else if (statusCode == 941) {
		_instance->setOnSprite(2);
		if (SelectRoleScene::_index == 2) { _instance->myTurn(true); }
		else { _instance->myTurn(); }
	}
	else if (statusCode == 951) {
		NetworkGameOverScene::_Loser = QJson::getString("result");
		CCLOG("loser %s", NetworkGameOverScene::_Loser.c_str());
		QE_ReplaceScene(NetworkGameOverScene);
	}
	else if (statusCode == 961){
		_instance->addListViewElement(QJson::getString("msg"), "scoundrelPP.png");
	}
	else if (statusCode == 971){
		_instance->addListViewElement(QJson::getString("msg"), "babyPP.png");
	}
	else if (statusCode == 981){
		_instance->addListViewElement(QJson::getString("msg"), "refereePP.png");
	}
}

void NetworkGameScene::initMenu(){
	QE_CreateSpriteMenu(40, 520, "back.png", NetworkGameScene, back);
	QE_CreateSpriteMenu2(865, 55, "send.png", "sendPressed.png", NetworkGameScene, send);
	_sendMenu = QMenu::_menu;
}

void NetworkGameScene::send(){
	string msg = _msgBox->getText();
	if (msg != ""){
		Connect::createMsg();
		Connect::addMsg("msg", QE_ToJStr(_msgBox->getText()));
		Connect::sendMsg();
		_msgBox->setText("");
		_confirmSpr->setVisible(true);
		myTurn(false);
	}
}

void NetworkGameScene::back() { QE_ReplaceScene(NetworkGameOverScene); };

void NetworkGameScene::initEditBox(){
	_spr = Sprite::create("editBox.png");
	_msgBox = _box = createEditBox("editBox.png", "editBoxPressed.png");
	_box->setPosition(Vec2(53, 20));
	_box->setPlaceHolder("    请输入聊天信息");
	_box->setSize(_spr->getContentSize());
}

void NetworkGameScene::initSprits(){
	_onSprites.clear();
	QE_addBgSprite;
	createSprite(165, 160, "scoundrel");
	createSprite(165, 430, "baby");
	createSprite(165, 295, "referee");
}

void NetworkGameScene::createSprite(int x, int y, string identity){
	_spr = Sprite::create(identity + ".png");
	_spr->setPosition(x, y);
	addChild(_spr);

	_spr = Sprite::create(identity + "'sTurn.png");
	_spr->setPosition(x, y);
	_spr->setVisible(false);
	addChild(_spr);
	_onSprites.push_back(_spr);
}

void NetworkGameScene::setOnSprite(int index){
	for (size_t i = 0; i < _onSprites.size(); i++){ _onSprites[i]->setVisible(false); }
	_onSprites[index]->setVisible(true);
}

void NetworkGameScene::initListView(){
	_spr = Sprite::create("chatBg.png");
	addChild(_spr);
	_spr->setPosition(600, 310);
	_spr->setAnchorPoint(Vec2(0.5, 0.5));

	_spr = Sprite::create("chat.png");
	_listView = ListView::create();
	_listView->setDirection(ScrollView::Direction::BOTH);
	_listView->setBounceEnabled(true);//回弹效果
	_listView->setBackGroundImage("chat.png");
	_listView->setBackGroundImageScale9Enabled(true);
	_listView->setContentSize(_spr->getContentSize());
	_listView->setAnchorPoint(Vec2(0.5, 0.5));
	_listView->setPosition(Vec2(600, 310));
	addChild(_listView);
}

void NetworkGameScene::addListViewElement(const string msg, const string pic){
	RichText* richText = RichText::create();
	richText->setContentSize(Size(_listView->getContentSize().width, 30));
	richText->setPosition(Vec2(-_listView->getContentSize().width, 0));
	richText->setAnchorPoint(Vec2(0, 0));

	richText->pushBackElement(RichElementImage::create(3, Color3B::WHITE, 255, pic));
	richText->pushBackElement(RichElementText::create(2, Color3B::RED, 255, " : " + msg, QE_Font, 20));

	_listView->insertCustomItem(richText, 0);
}

void NetworkGameScene::initConfrimSprite(){
	_confirmSpr = createSprite("confirm.png");
	//_confirmSpr->setVisible(false);
	createSprite(630, "yes.png", bind(&NetworkGameScene::yes, this));
	createSprite(320, "no.png", bind(&NetworkGameScene::no, this));

	_judgeSpr = createSprite("refereeConfirm.png");
	//_judgeSpr->setVisible(false);
	createSprite(300, "babyWin.png", bind(&NetworkGameScene::babyWin, this));
	createSprite(475, "scoundrelWin.png", bind(&NetworkGameScene::scoundrelWin, this));
	createSprite(650, "goOn.png", bind(&NetworkGameScene::goOn, this));
}

Sprite* NetworkGameScene::createSprite(const string& picture){
	_spr = Sprite::create(picture);
	addChild(_spr);
	_spr->setPosition(540, 270);
	_spr->setVisible(false);
	return _spr;
}

void NetworkGameScene::createSprite(int x, const string& picture, const ccMenuCallback& callback){
	_menu = QMenu::createMenuSprite(picture, callback);
	_menu->setPosition(x, 200);
	_spr->addChild(_menu);
}

void NetworkGameScene::myTurn(bool isMyTurn){
	_sendMenu->setEnabled(isMyTurn);
	_msgBox->setEnabled(isMyTurn);
}

void NetworkGameScene::endChat(){
	Connect::createMsg();
	Connect::addMsg("end", "");
	Connect::sendMsg();
}

void NetworkGameScene::yes(){
	_confirmSpr->setVisible(false);
	if (SelectRoleScene::_index == 2) { _judgeSpr->setVisible(true); }
	else { endChat(); }
}

void NetworkGameScene::no(){
	_confirmSpr->setVisible(false);
	myTurn(true);
}

void NetworkGameScene::babyWin(){
	//NetworkGameOverScene::_Loser = "scoundrelLose";
	//QE_ReplaceScene(NetworkGameOverScene);
	Connect::createMsg();
	Connect::addMsg("result", "scoundrelLose");
	Connect::sendMsg();
	_judgeSpr->setVisible(false);
}

void NetworkGameScene::scoundrelWin(){
	//NetworkGameOverScene::_Loser = "babyLose";
	//QE_ReplaceScene(NetworkGameOverScene);
	Connect::createMsg();
	Connect::addMsg("result", "babyLose"); 
	Connect::sendMsg();
	_judgeSpr->setVisible(false);
}

void NetworkGameScene::goOn(){
	_judgeSpr->setVisible(false);
	endChat();
}

void NetworkGameScene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	Connect::connect(Connect::Event::Dialog);
}