#pragma execution_character_set("utf-8")

#include "Connect.h"

WebSocket* Connect::_ws = nullptr;
bool Connect::_isConnecting = false;
string Connect::_addr = "ws://10.6.32.1:56/";
Connect::Event Connect::_nowEvent;

QE_SINGLETON_CPP(Connect);

void Connect::connect(Event nowEvent)
{
	_nowEvent = nowEvent;
	if (!_ws) { Connect::getInstance()->initSocket(); };
}

void Connect::initSocket()
{
	_isConnecting = true;
	_ws = new WebSocket();
	if (!_ws->init(*this, _addr))
	{
		CC_SAFE_DELETE(_ws);
	}
}

void Connect::createMsg()
{
	QJson::emptyDoc();
	addMsg("消息类型", QE_strToJStr(getNowEvent()));
}

string Connect::getNowEvent()
{
	if (_nowEvent == ConnectServer) { return "ConnectServer"; }
	else if (_nowEvent == SignUp) { return "SignUp"; }
	else if (_nowEvent == SignIn) { return "SignIn"; }
	else if (_nowEvent == GetRooms) { return "GetRooms"; }
	else if (_nowEvent == CreateRoom) { return "CreateRoom"; }
	else if (_nowEvent == EnterRoom) { return "EnterRoom"; }
	else if (_nowEvent == Dialog) { return "Dialog"; }
}

string Connect::getStatus(Status status)
{
	//ConnectServer = 0, //连接服务器事件
	if (status == ConnectServerCase1Failed) { return ""; }
	else if (status == ConnectServerCase1Successful) { return "已连接服务器成功，正在转入登录界面。。。"; }
	else if (status == ConnectServerCase2Failed) { return "正在连接：" + _addr + "\n请稍后，若长时间未正常连接请再尝试进行重连"; }
	//SignUp = 1, //注册事件
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
	else if (status == ConnectServerCase1Successful) { return "SignUp"; }
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
	_isConnecting = false;
	string info = "连接服务器成功";
	if (_nowEvent == ConnectServer) { ConnectServerScene::dealServerResponse(ConnectStatus(ConnectServerCase1Successful)); }
	else if (_nowEvent == SignUp) { SignUpScene::dealServerResponse(""); }
	else if (_nowEvent == SignIn) { SignInScene::dealServerResponse("连接服务器成功，请登录，如果没有账号请先注册。"); }
}

void Connect::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
	if (ws != _ws) { return; }
	CCLOG("收到信息：%s", data.bytes);
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

	if (_nowEvent == ConnectServer) { ConnectServerScene::dealServerResponse("连接服务器失败，请重试"); }
	else if (_nowEvent == SignUp) { SignUpScene::dealServerResponse(errInfo); }
	else if (_nowEvent == SignIn) { SignInScene::dealServerResponse(errInfo); }
}

void Connect::onError(WebSocket* ws, const WebSocket::ErrorCode& error)
{
	if (ws != _ws) { return; }
	_ws->close();
}