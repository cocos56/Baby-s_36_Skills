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
	Menu* menu = QMenu::createMenuLabel("连接", bind(&ConnectServerScene::connect, this, 1));
	menu->setPosition(680, 390);
	addChild(menu);

	menu = QMenu::createMenuLabel("连接", bind(&ConnectServerScene::connect, this, 2));
	menu->setPosition(680, 340);
	addChild(menu);
}

void ConnectServerScene::connect(int n)
{
	if (Connect::_isConnecting)
	{
		_logLabel->setString(ConnectStatus(ConnectServerCase2Failed));
		return;
	}
	if (Connect::_ws)
	{
		_logLabel->setString(ConnectStatus(ConnectServerCase1Successful));
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

void ConnectServerScene::dealServerResponse(string str)
{ 
	_logLabel->setString(str);
	if (str == ConnectStatus(ConnectServerCase1Successful))
	{
		getInstance()->scheduleOnce(schedule_selector(ConnectServerScene::enterSignInScene), 1.0f);
	}
}

void ConnectServerScene::enterSignInScene(float f) 
{ 
	Director::getInstance()->replaceScene(SignInScene::createScene());
}

void ConnectServerScene::initEditBox()
{
	createLabel("Coco's Server")->setPosition(140, 390);
	//输入IP的框
	_ip1Box = _box = createEditBox("green_edit.png", "10.6.32.1", 15);
	_box->setPosition(Vec2(320, 380));
	//输入端口的框
	_port1Box = _box = createEditBox("orange_edit.png", "56", 5);
	_box->setSize(Size(80, 38));
	_box->setPosition(Vec2(570, 380));

	createLabel("本地服务器")->setPosition(140, 340);
	//输入IP的框
	_ip2Box = _box = createEditBox("green_edit.png", "127.0.0.1", 15);
	_box->setPosition(Vec2(320, 330));
	//输入端口的框
	_port2Box = _box = createEditBox("orange_edit.png", "56", 5);
	_box->setSize(Size(80, 38));
	_box->setPosition(Vec2(570, 330));
}