#pragma execution_character_set("utf-8")

#include "SelectRoleScene.h"

RadioButtonGroup* SelectRoleScene::_radioButtonGroup;

QE_SINGLETON2_CPP(SelectRoleScene);

QE_CreateSceneFromLayer_CPP(SelectRoleScene);
	paths = { "fonts" };
	QE_SetResourcesSearchDir;

	_instance = this;

	Connect::connect(Connect::Event::GetRooms);

	initLabel();
	initMenu();
	initRadioButton();
	return true;
}

void SelectRoleScene::dealServerResponse(int statusCode)
{
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
	//if (statusCode == 381)
	//{
	//	getInstance()->scheduleOnce(schedule_selector(SelectRoleScene::enterSignInScene), 3.0f);
	//}
}

void SelectRoleScene::enterSignInScene(float f) { QE_ReplaceScene(SignInScene); }

void SelectRoleScene::initLabel()
{
	createLabel("选择身份");
	_label->setPosition(420, 460);
	createLabel("房间号：");
	_label->setPosition(350, 400);
	createLabel("房间名：");
	_label->setPosition(350, 350);
	createLabel("宝宝");
	_label->setPosition(380, 300);
	createLabel("坏人");
	_label->setPosition(460, 300);
	createLabel("裁判");
	_label->setPosition(540, 300);

	_logLabel = createLabel("");
	_logLabel->setPosition(150, 100);
	if (Connect::_ws) { dealServerResponse(311); }
	else { dealServerResponse(310); }
}

void SelectRoleScene::initMenu()
{
	QE_CreateLabelMenu(420, 200, "确认进入", SelectRoleScene, createRoom);
	QE_CreateLabelMenuAgain(10, 500, "返回", SelectRoleScene, back);
}

void SelectRoleScene::createRoom()
{

}

void SelectRoleScene::joinRoom()
{

}

void SelectRoleScene::back() { QE_ReplaceScene(SignInScene); };

void SelectRoleScene::initRadioButton()
{
	_radioButtonGroup = RadioButtonGroup::create();
	addChild(_radioButtonGroup);

	for (int i = 0; i < 3; ++i)
	{
		RadioButton* radioButton = RadioButton::create("icon/btn_radio_off_holo.png", "icon/btn_radio_on_holo.png");
		float posX = 400 + 80 * i;
		radioButton->setPosition(Vec2(posX, 270));
		_radioButtonGroup->addRadioButton(radioButton);
		_radioButtonGroup->addEventListener(CC_CALLBACK_3(SelectRoleScene::onChangedRadioButtonGroup, this));

		addChild(radioButton);
	}
}

void SelectRoleScene::onChangedRadioButtonGroup(RadioButton* radioButton, int index, RadioButtonGroup::EventType type)
{
	CCLOG("RadioButton Index : %d", index);
}
