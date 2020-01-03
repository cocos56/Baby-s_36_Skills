#pragma execution_character_set("utf-8")

#include "ConnectServerScene.h"

EditBox* ConnectServerScene::_ip1Box, * ConnectServerScene::_port1Box, * ConnectServerScene::_ip2Box, * ConnectServerScene::_port2Box, * ConnectServerScene::_ip3Box, * ConnectServerScene::_port3Box, * ConnectServerScene::_ip4Box, * ConnectServerScene::_port4Box, * ConnectServerScene::_ip5Box, * ConnectServerScene::_port5Box;

QE_SINGLETON2_CPP(ConnectServerScene);

QE_CreateSceneFromLayer_CPP(ConnectServerScene);
	paths = { "ConnectServerScene" };
	QE_SetResourcesSearchDir;
	QE_addBgSprite;
	
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
	QE_CreateLabelMenu(680, 340, "连接", ConnectServerScene, connect, 2);
	QE_CreateLabelMenu(680, 290, "连接", ConnectServerScene, connect, 3);
	QE_CreateLabelMenu(680, 230, "连接", ConnectServerScene, connect, 4);
	QE_CreateLabelMenu(680, 190, "连接", ConnectServerScene, connect, 5);
	QE_CreateLabelMenu(10, 500, "返回", ConnectServerScene, back);
}

void ConnectServerScene::back()
{
	QE_ReplaceScene(GameInterfaceScene);
}

void ConnectServerScene::connect(int n)
{
	if (Connect::_isConnecting){ dealServerResponse(120); return; }
	else if (Connect::_ws){ dealServerResponse(111); return; }
	
	string ip, port;
	if (n == 1){
		ip = _ip1Box->getText();
		port = _port1Box->getText();
	}
	else if (n == 2){
		ip = _ip2Box->getText();
		port = _port2Box->getText();
	}
	else if (n == 3) {
		ip = _ip3Box->getText();
		port = _port3Box->getText();
	}
	else if (n == 4) {
		ip = _ip4Box->getText();
		port = _port4Box->getText();
	}
	else if (n == 5) {
		ip = _ip5Box->getText();
		port = _port5Box->getText();
	}
	Connect::_addr = String::createWithFormat("ws://%s:%s/", ip.c_str(), port.c_str())->getCString();
	_logLabel->setString("正在连接：" + Connect::_addr);
	Connect::connect(Connect::Event::ConnectServer);
}

void ConnectServerScene::dealServerResponse(int statusCode)
{ 
	string status = Connect::getStatus(statusCode);
	dealServerResponse(status);
	QMessageBox(status);
	if (statusCode == 111)
	{
		QE_ReplaceScene(SignInScene);
	}
}

void ConnectServerScene::disConnect()
{
	//if (COCOS2D_DEBUG) { return; }
	
	if (Connect::_nowEvent != Connect::Event::ConnectServer) { 
		QMessageBox("已与服务器：" + Connect::_addr + " 失去连接，请重新连接服务器。");
		QE_ReplaceScene(ConnectServerScene);
	}
	else { QMessageBox("无法连接到服务器：" + Connect::_addr + " ，请重新选择服务器。"); }
}
	

void ConnectServerScene::initEditBox()
{
	createLabel("互联网服务器1")->setPosition(140, 390);
	//输入IP的框
	_ip1Box = _box = createEditBox("editBox.png", "coco56.top", 15);
	_box->setPosition(Vec2(320, 380));
	_box->setInputMode(EditBox::InputMode::URL);
	//输入端口的框
	_port1Box = _box = createEditBox("editBox.png", "56", 5);
	_box->setSize(Size(80, 38));
	_box->setPosition(Vec2(570, 380));
	_box->setInputMode(EditBox::InputMode::NUMERIC);

	createLabel("互联网服务器2")->setPosition(140, 340);
	//输入IP的框
	_ip2Box = _box = createEditBox("editBox.png", "47.100.119.84", 15);
	_box->setPosition(Vec2(320, 330));
	_box->setInputMode(EditBox::InputMode::URL);
	//输入端口的框
	_port2Box = _box = createEditBox("editBox.png", "33414", 5);
	_box->setSize(Size(80, 38));
	_box->setPosition(Vec2(570, 330));
	_box->setInputMode(EditBox::InputMode::NUMERIC);

	createLabel("校园网服务器")->setPosition(140, 290);
	//输入IP的框
	_ip3Box = _box = createEditBox("editBox.png", "10.6.32.1", 15);
	_box->setPosition(Vec2(320, 280));
	_box->setInputMode(EditBox::InputMode::URL);
	//输入端口的框
	_port3Box = _box = createEditBox("editBox.png", "56", 5);
	_box->setSize(Size(80, 38));
	_box->setPosition(Vec2(570, 280));
	_box->setInputMode(EditBox::InputMode::NUMERIC);

	createLabel("自组网服务器")->setPosition(140, 240);
	//输入IP的框
	_ip4Box = _box = createEditBox("editBox.png", "10.1.1.1", 15);
	_box->setPosition(Vec2(320, 230));
	_box->setInputMode(EditBox::InputMode::URL);
	//输入端口的框
	_port4Box = _box = createEditBox("editBox.png", "56", 5);
	_box->setSize(Size(80, 38));
	_box->setPosition(Vec2(570, 230));
	_box->setInputMode(EditBox::InputMode::NUMERIC);

	createLabel("本机服务器")->setPosition(140, 190);
	//输入IP的框
	_ip5Box = _box = createEditBox("editBox.png", "127.0.0.1", 15);
	_box->setPosition(Vec2(320, 180));
	_box->setInputMode(EditBox::InputMode::URL);
	//输入端口的框
	_port5Box = _box = createEditBox("editBox.png", "56", 5);
	_box->setSize(Size(80, 38));
	_box->setPosition(Vec2(570, 180));
	_box->setInputMode(EditBox::InputMode::NUMERIC);
}

