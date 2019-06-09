# pragma execution_character_set("utf-8")

#include "Connect.h"

WebSocket* Connect::_ws = nullptr;
bool Connect::_isConnecting = false;
string Connect::_addr="ws://10.6.32.1:56/", Connect::_nowEvent;

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

void Connect::createMsg()
{
	QJson::emptyDoc();
	addMsg("消息类型", QE_strToJStr(_nowEvent));
}

void Connect::addMsg(JString key, JString value)
{
	QJson::addMember(key, value);
}

void Connect::sendMsg()
{
	if (!_ws) { return; }
	_ws->send(QJson::getString());
}

void Connect::onOpen(WebSocket* ws)
{
	//进行这样的判断是因为WebSocket对象没有setTag方法0
	if (ws != _ws){return;}
}

void Connect::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
	if (ws != _ws) { return; }
	CCLOG("onMsg:%s", data.bytes);
	QJson::initDocWithString(data.bytes);
	string msgT = QJson::getString("消息类型");
	if (msgT == "注册响应")
	{
		SignUpScene::dealServerResponse();
	}
}

void Connect::onClose(WebSocket* ws)
{
	if (ws != _ws) { return; }
	_ws = nullptr;
	_isConnecting = false;

	string errInfo = "已与服务器失去连接，请返回服务器连接界面重连";

	if (_nowEvent == "注册") { SignUpScene::dealServerResponse(errInfo); }
}

void Connect::onError(WebSocket* ws, const WebSocket::ErrorCode& error)
{
	if (ws != _ws) { return; }
	_ws->close();
}