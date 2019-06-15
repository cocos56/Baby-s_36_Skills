#pragma execution_character_set("utf-8")

#include "ConnectServerScene.h"

EditBox* ConnectServerScene::_ip1Box, * ConnectServerScene::_port1Box, * ConnectServerScene::_ip2Box, * ConnectServerScene::_port2Box;

QE_SINGLETON2_CPP(ConnectServerScene);

QE_CreateSceneFromLayer_CPP(ConnectServerScene);
	paths = { "fonts" };
	QE_SetResourcesSearchDir;
	
	_instance = this;

	initLabel();
	initMenu();
	initEditBox();

	return true;
}

void ConnectServerScene::initLabel()
{
	createLabel("服务器名")->setPosition(140, 450);
	createLabel("IP地址")->setPosition(320, 450);
	createLabel("端口")->setPosition(570, 450);
	createLabel("操作")->setPosition(680, 450);

	_logLabel = createLabel("");
	_logLabel->setPosition(100, 100);
}

void ConnectServerScene::initMenu()
{
	QE_CreateLabelMenu(680, 390, "连接", ConnectServerScene, connect, 1);
	QE_CreateLabelMenuAgain(680, 340, "连接", ConnectServerScene, connect, 2);
	QE_CreateLabelMenuAgain(10, 500, "返回", ConnectServerScene, back);
}

void ConnectServerScene::back()
{

}

void ConnectServerScene::connect(int n)
{
	if (Connect::_isConnecting)
	{
		_logLabel->setString(GetConnectStatus(ConnectServerCase2Failed));
		return;
	}
	if (Connect::_ws)
	{
		_logLabel->setString(GetConnectStatus(ConnectServerCase1Successful));
		getInstance()->scheduleOnce(schedule_selector(ConnectServerScene::enterSignInScene), 1.0f);
		return;
	}
	string ip, port;
	if (n == 1)
	{
		ip = _ip1Box->getText();
		port = _port1Box->getText();
	}
	else if (n == 2)
	{
		ip = _ip2Box->getText();
		port = _port2Box->getText();
	}
	Connect::_addr = String::createWithFormat("ws://%s:%s/", ip.c_str(), port.c_str())->getCString();
	_logLabel->setString("正在连接：" + Connect::_addr);
	Connect::connect(Connect::Event::ConnectServer);
}

void ConnectServerScene::dealServerResponse(int statusCode)
{ 
	dealServerResponse(statusCode);
	if (statusCode == 111)
	{
		getInstance()->scheduleOnce(schedule_selector(ConnectServerScene::enterSignInScene), 1.0f);
	}
}

void ConnectServerScene::enterSignInScene(float f) { QE_ReplaceScene(SignInScene); }

void ConnectServerScene::initEditBox()
{
	createLabel("Coco's Server")->setPosition(140, 390);
	//输入IP的框
	_ip1Box = _box = createEditBox("green_edit.png", "10.6.32.1", 15);
	_box->setPosition(Vec2(320, 380));
	_box->setInputMode(EditBox::InputMode::URL);
	//输入端口的框
	_port1Box = _box = createEditBox("orange_edit.png", "56", 5);
	_box->setSize(Size(80, 38));
	_box->setPosition(Vec2(570, 380));
	_box->setInputMode(EditBox::InputMode::NUMERIC);

	createLabel("本地服务器")->setPosition(140, 340);
	//输入IP的框
	_ip2Box = _box = createEditBox("green_edit.png", "127.0.0.1", 15);
	_box->setPosition(Vec2(320, 330));
	_box->setInputMode(EditBox::InputMode::URL);
	//输入端口的框
	_port2Box = _box = createEditBox("orange_edit.png", "56", 5);
	_box->setSize(Size(80, 38));
	_box->setPosition(Vec2(570, 330));
	_box->setInputMode(EditBox::InputMode::NUMERIC);
}