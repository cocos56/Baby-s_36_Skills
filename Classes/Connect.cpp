#include "Connect.h"

SIOClient* Connect::_sioClient;
bool Connect::isConnect = false;
string Connect::addr;

QE_SINGLETON_CPP(Connect);

void Connect::connect()
{
	if (!isConnect) { Connect::getInstance()->initSocket(); };
}

void Connect::initSocket()
{
	string ip = "10.6.32.1";
	//ip = "localhost";
	string port = "56";
	addr = "http://" + ip + ":" + port + "/";
	_sioClient = SocketIO::connect(addr, *this);
	//注册服务器端事件
	_sioClient->on("callClientEvent", CC_CALLBACK_2(Connect::callClientEvent, this));
}

//委托协议方法
void Connect::onConnect(SIOClient* client)
{
	isConnect = true;
	CCLOG("HelloWorld::onConnect called");
	String* s = String::createWithFormat("%s connected!", client->getTag());
}

void Connect::onMessage(SIOClient* client, const std::string& data)
{
	CCLOG("HelloWorld::onMessage received: %s", data.c_str());
	String* s = String::createWithFormat("%s  received message.", client->getTag());
}

void Connect::onClose(SIOClient* client)
{
	isConnect = false;

	CCLOG("HelloWorld::onClose called");

	if (client == _sioClient) {
		_sioClient = nullptr;
	}
}

void Connect::onError(SIOClient* client, const std::string& data)
{
	isConnect = false;

	CCLOG("HelloWorld::onError received: %s", data.c_str());
	String* s = String::createWithFormat("%s   received error .", client->getTag());
}

void Connect::callClientEvent(SIOClient* client, const std::string& data)
{
	CCLOG("HelloWorld::callClientEvent received: %s", data.c_str());
	String* s = String::createWithFormat("%s Server CallBack", client->getTag());
}