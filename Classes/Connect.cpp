#include "Connect.h"
#include "SignInScene.h"

WebSocket* Connect::_ws = nullptr;
bool Connect::isConnect = false;
string Connect::addr;

QE_SINGLETON_CPP(Connect);

void Connect::connect()
{
	if (!isConnect) { Connect::getInstance()->initSocket(); };
}

void Connect::initSocket()
{
	string ip;
	ip	= "10.6.32.1";
	//ip = "localhost";
	int port = 56;
	addr = String::createWithFormat("ws://%s:%d/", ip.c_str(), port)->getCString();
	//addr = "ws://" + ip + ":" + port + "/";
	_ws = new WebSocket();
	if (!_ws->init(*this, addr))
	{
		CC_SAFE_DELETE(_ws);
	}
}

//委托协议方法
void Connect::onOpen(cocos2d::network::WebSocket* ws)
{
	//进行这样的判断是因为WebSocket对象没有setTag方法0
	if (ws != _ws){return;}

	updateStatus(true);
	CCLOG("Connect::onOpen called");
	_ws->send("Hello, I am cocos2d-x, send()");
}

void Connect::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
	if (ws != _ws) { return; }
	updateStatus(true);
	CCLOG("Connect::onMessage received: %s", data.bytes);
}

void Connect::onClose(cocos2d::network::WebSocket* ws)
{
	if (ws != _ws) { return; }
	updateStatus(false);
	CCLOG("Connect::onClose called");
	_ws = nullptr;
}

void Connect::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
	if (ws != _ws) { return; }

	updateStatus(false);
	SignInScene::logLabel->setString("onError:" + to_string(int(error)) + "||" + addr);
	_ws->close();
	CCLOG("HelloWorld::onError received: %d", error);
}

void Connect::updateStatus(bool status)
{
	isConnect = status;
	SignInScene::updateLabel();
}