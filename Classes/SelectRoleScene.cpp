﻿#pragma execution_character_set("utf-8")

#include "SelectRoleScene.h"

RadioButtonGroup* SelectRoleScene::_radioButtonGroup;
vector<RichText*> SelectRoleScene::_texts;
RichText* SelectRoleScene::_richText;
int SelectRoleScene::_index;

QE_SINGLETON2_CPP(SelectRoleScene);

QE_CreateSceneFromLayer_CPP(SelectRoleScene);
	paths = { "fonts", "SelectRoleScene" };
	QE_SetResourcesSearchDir;
	QE_addBgSpriteToThis;

	_instance = this;

	Connect::connect(Connect::Event::SelectRole);

	initLabel();
	initMenu();
	initRadioButton();
	return true;
}

void SelectRoleScene::dealServerResponse(int statusCode)
{
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
	QMessageBox(status);
	if (statusCode == 731) { QE_ReplaceScene(WaitingNetworkGameScene); }
}

void SelectRoleScene::initLabel()
{
	NW_InitLogLabel(150, 100);
}

RichText* SelectRoleScene::createRichText(int x, int y, string roleName, string fileName)
{
	//创建RichText对象
	_richText = RichText::create();
	//设置是否忽略用户定义的内容大小
	_richText->ignoreContentAdaptWithSize(false);
	//设置内容大小
	_richText->setContentSize(Size(500, 50));
	_richText->setPosition(Vec2(x, y));
	_richText->setAnchorPoint(Vec2(0, 0));

	//创建文本类型的RichElement对象
	RichElementText* re1 = RichElementText::create(0, Color3B::WHITE, 255, roleName, QE_Font, 24);
	//创建图片类型的RichElement对象
	RichElementImage* re2 = RichElementImage::create(6, Color3B::WHITE, 255, fileName);
	//创建换行RichElement对象
	RichElementNewLine* newLine = RichElementNewLine::create(77, Color3B::WHITE, 255);

	_richText->pushBackElement(re1);
	//richText->pushBackElement(newLine);
	_richText->pushBackElement(re2);

	_texts.push_back(_richText);
	addChild(_richText);
	return _richText;
}

void SelectRoleScene::setTextsColor(int n)
{
	for (size_t i = 0; i < _texts.size(); i++)
	{
		_texts[i]->setColor(Color3B::WHITE);
	}
	_texts[n]->setColor(Color3B(153, 204, 0));
}

void SelectRoleScene::initMenu()
{
	QE_CreateLabelMenu(420, 200, "开始比拼", SelectRoleScene, confirm);
	QE_CreateLabelMenuAgain(10, 500, "返回", SelectRoleScene, back);
}

void SelectRoleScene::confirm()
{
	Connect::createMsg();
	Connect::addMsg("type", _index);
	//Connect::addMsg("un", QE_strToJStr(SignInScene::_un));
	Connect::addMsg("un", SignInScene::_un);
	Connect::sendMsg();
}

void SelectRoleScene::back() { QE_ReplaceScene(SignInScene); };

void SelectRoleScene::initRadioButton()
{
	_radioButtonGroup = RadioButtonGroup::create();
	addChild(_radioButtonGroup);

	for (int i = 0; i < 4; ++i)
	{
		RadioButton* radioButton = RadioButton::create("icon/btn_radio_off_holo.png", "icon/btn_radio_on_holo.png");
		float posX = 270 + 120 * i;
		float posY = 500 - 140 * i;
		radioButton->setPosition(Vec2(posX, posY));
		_radioButtonGroup->addRadioButton(radioButton);
		_radioButtonGroup->addEventListener(CC_CALLBACK_3(SelectRoleScene::onChangedRadioButtonGroup, this));
		if (i == 0) { radioButton->setVisible(false); }
		addChild(radioButton);
	}
}

void SelectRoleScene::onChangedRadioButtonGroup(RadioButton* radioButton, int index, RadioButtonGroup::EventType type)
{
	_index = index;
}
