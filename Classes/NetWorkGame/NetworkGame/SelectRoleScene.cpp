#pragma execution_character_set("utf-8")

#include "SelectRoleScene.h"

RadioButtonGroup* SelectRoleScene::_radioButtonGroup;
int SelectRoleScene::_index = 0;

QE_SINGLETON2_CPP(SelectRoleScene);

QE_CreateSceneFromLayer_CPP(SelectRoleScene);
	paths = { "fonts", "SelectRoleScene" };
	QE_SetResourcesSearchDir;

	_instance = this;

	Connect::connect(Connect::Event::SelectRole);

	initSprits();
	initLabel();
	initMenu();
	initRadioButton();
	return true;
}

void SelectRoleScene::initSprits(){
	QE_addBgSprite;
	QE_addBgSpriteWithName("baby.png");
	QE_addBgSpriteWithName("referee.png");
	QE_addBgSpriteWithName("scoundrel.png");
	QE_addBgSpriteWithName("bar.png");
}

void SelectRoleScene::dealServerResponse(int statusCode){
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
	QMessageBox(status);
	if (statusCode == 731) { QE_ReplaceScene(WaitingNetworkGameScene); }
}

void SelectRoleScene::initLabel(){
	createLabel(GetRoomsScene::_name)->setPosition(340, 505);
	NW_InitLogLabel(10, 80);
}

void SelectRoleScene::initMenu(){
	QE_CreateSpriteMenu2(470, 40, "confirm.png", "confirmPressed.png", SelectRoleScene, confirm);
	QE_CreateSpriteMenu(40, 520, "back.png", SelectRoleScene, back);
}

void SelectRoleScene::confirm(){
	Connect::createMsg();
	Connect::addMsg("type", _index);
	Connect::addMsg("un", QE_strToJStr(SignInScene::_un));
	Connect::sendMsg();
}

void SelectRoleScene::back() { QE_ReplaceScene(GetRoomsScene); };

void SelectRoleScene::initRadioButton(){
	_radioButtonGroup = RadioButtonGroup::create();
	addChild(_radioButtonGroup);

	for (int i = 0; i < 4; ++i){
		RadioButton* radioButton = RadioButton::create("radioOff.png", "radioOn.png");
		float posX = 270 + 120 * i;
		float posY = 500 - 140 * i;
		radioButton->setPosition(Vec2(posX, posY));
		_radioButtonGroup->addRadioButton(radioButton);
		_radioButtonGroup->addEventListener(CC_CALLBACK_3(SelectRoleScene::onChangedRadioButtonGroup, this));
		if (i == 0) { radioButton->setVisible(false); }
		addChild(radioButton);
	}
}

void SelectRoleScene::onChangedRadioButtonGroup(RadioButton* radioButton, int index, RadioButtonGroup::EventType type){ _index = index; }
