# pragma execution_character_set("utf-8")

#include "ConnectServerScene.h"

EditBox* ConnectServerScene::_ip1Box, * ConnectServerScene::_port1Box, * ConnectServerScene::_ip2Box, * ConnectServerScene::_port2Box;
Label* ConnectServerScene::_logLabel;

QE_CreateSceneFromLayer_CPP(ConnectServerScene);
	paths = { "fonts" };
	QE_SetResourcesSearchDir;
	
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

Label* ConnectServerScene::createLabel(string text)
{
	Label* label = Label::create(text, QE_Font, 25);
	label->setAnchorPoint(Vec2(0, 0));
	addChild(label);
	return label;
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
		_logLabel->setString("正在连接：" + Connect::_addr + "\n请稍后，若长时间未正常连接请再尝试进行重连");
		return;
	}
	Connect::_isConnecting = true;
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
	Connect::connect("连接服务器");
}

void ConnectServerScene::initEditBox()
{
	EditBox* box;
	createLabel("Coco's Server")->setPosition(140, 390);
	//输入IP的框
	_ip1Box = box = createEditBox("green_edit.png", "10.6.32.1", 15);
	box->setPosition(Vec2(320, 380));
	//输入端口的框
	_port1Box = box = createEditBox("orange_edit.png", "56", 5);
	box->setSize(Size(80, 38));
	box->setPosition(Vec2(570, 380));

	createLabel("本地服务器")->setPosition(140, 340);
	//输入IP的框
	_ip2Box = box = createEditBox("green_edit.png", "127.0.0.1", 15);
	box->setPosition(Vec2(320, 330));
	//输入端口的框
	_port2Box = box = createEditBox("orange_edit.png", "56", 5);
	box->setSize(Size(80, 38));
	box->setPosition(Vec2(570, 330));
}

EditBox* ConnectServerScene::createEditBox(string normalPngFile, string text, int maxLength)
{
	EditBox* box = EditBox::create(Size(210, 38), Scale9Sprite::create(normalPngFile), Scale9Sprite::create("wite_edit.png"));
	box->setFontName(QE_Font);
	box->setFontSize(25);
	box->setText(text.c_str());
	box->setFontColor(Color3B(0, 0, 255));
	box->setPlaceholderFontName(QE_Font);
	box->setPlaceholderFontSize(25);
	box->setPlaceHolder(text.c_str()); //当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符
	box->setPlaceholderFontColor(Color3B(255, 0, 0));
	box->setMaxLength(maxLength);   //设置文本框中文本的最大长度
	box->setInputMode(EditBox::InputMode::ANY);//输入键盘模式,任何符号
	box->setAnchorPoint(Vec2(0, 0));
	box->setDelegate(this);//开启委托，文本框代理，需要实现EditBoxDelegate代理中的方法，就可以对EditBox进行控制
	addChild(box);
	return box;
}