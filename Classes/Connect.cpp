#include "Connect.h"
#include "SignInScene.h"

WebSocket* Connect::_ws = nullptr;
bool Connect::_isConnecting = false;
string Connect::_addr="ws://10.6.32.1:56/";

QE_SINGLETON_CPP(Connect);

void Connect::connect()
{
	if (!_ws) { Connect::getInstance()->initSocket(); };
}

void Connect::initSocket()
{
	_ws = new WebSocket();
	if (!_ws->init(*this, _addr))
	{
		CC_SAFE_DELETE(_ws);
	}
}

//委托协议方法
void Connect::onOpen(cocos2d::network::WebSocket* ws)
{
	//进行这样的判断是因为WebSocket对象没有setTag方法0
	if (ws != _ws){return;}

	CCLOG("Connect::onOpen called");
	_ws->send("Hello, I am cocos2d-x, send()");

	Director::getInstance()->replaceScene(SignInScene::createScene());
}

void Connect::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
	if (ws != _ws) { return; }
	CCLOG("Connect::onMessage called");
}

void Connect::onClose(cocos2d::network::WebSocket* ws)
{
	if (ws != _ws) { return; }
	_ws = nullptr;
	_isConnecting = false;
	CCLOG("Connect::onClose called");
}

void Connect::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
	if (ws != _ws) { return; }
	CCLOG("Connect::onError called");
	_ws->close();
}