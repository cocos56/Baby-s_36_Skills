#pragma execution_character_set("utf-8")

#include "SocketIOTestLayer.h"

SIOClient* SocketIOTestLayer::_sioClient;
bool SocketIOTestLayer::isConnect = false;
string SocketIOTestLayer::addr;
Label* SocketIOTestLayer::label = nullptr, * SocketIOTestLayer::logLabel=nullptr;

QE_SINGLETON_CPP(SocketIOTestLayer);

QE_CreateSceneFromLayer_CPP(SocketIOTestLayer);
	paths = { "fonts" };
	QE_SetResourcesSearchDir;

	label = Label::create("SIO", "Marker Felt.ttf", 20);
	label->setPosition(10, 270);
	label->setAnchorPoint(Vec2(0, 0));
	addChild(label);

	logLabel = Label::create("SIO LOG", "Marker Felt.ttf", 20);
	logLabel->setPosition(10, 220);
	logLabel->setAnchorPoint(Vec2(0, 0));
	addChild(logLabel);

	connect();

	return true;
}

void SocketIOTestLayer::updateLabel()
{
	if (SocketIOTestLayer::isConnect) { label->setString("Successful"); }
	else { label->setString("Failed"); }
}

void SocketIOTestLayer::connect()
{
	if (!isConnect) { SocketIOTestLayer::getInstance()->initSocket(); };
}

void SocketIOTestLayer::initSocket()
{
	string ip = "10.6.32.1";
	//ip = "localhost";
	string port = "80";
	addr = "ws://" + ip + ":" + port + "/";
	_sioClient = SocketIO::connect(addr, *this);
	//注册服务器端事件
	_sioClient->on("callClientEvent", CC_CALLBACK_2(SocketIOTestLayer::callClientEvent, this));
}

//委托协议方法
void SocketIOTestLayer::onConnect(SIOClient* client)
{
	updateStatus(true);
	CCLOG("HelloWorld::onConnect called");
	String* s = String::createWithFormat("%s connected!", client->getTag());
	_sioClient->send("Hello, I am cocos2d-x, send()");
}

void SocketIOTestLayer::onMessage(SIOClient* client, const std::string& data)
{
	updateStatus(true);
	CCLOG("HelloWorld::onMessage received: %s", data.c_str());
	String* s = String::createWithFormat("%s  received message.", client->getTag());
}

void SocketIOTestLayer::onClose(SIOClient* client)
{
	updateStatus(false);
	CCLOG("HelloWorld::onClose called");
	if (client == _sioClient) {
		_sioClient = nullptr;
	}
}

void SocketIOTestLayer::onError(SIOClient* client, const std::string& data)
{
	updateStatus(false);
	string error = data.c_str();
	logLabel->setString("onError:" + error + "||" + addr);
	//CCLOG("HelloWorld::onError received: %s", data.c_str());
	//String* s = String::createWithFormat("%s   received error .", client->getTag());
}

void SocketIOTestLayer::callClientEvent(SIOClient* client, const std::string& data)
{
	updateStatus(true);
	CCLOG("HelloWorld::callClientEvent received: %s", data.c_str());
	String* s = String::createWithFormat("%s Server CallBack", client->getTag());
}

void SocketIOTestLayer::updateStatus(bool status)
{
	isConnect = status;
	updateLabel();
}