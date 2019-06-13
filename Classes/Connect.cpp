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
	if (!_ws) { Connect::getInstance()->initSocket(); return; };
	if (_nowEvent == GetRooms) { createMsg(); sendMsg(); }
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

int Connect::getNowEvent()
{
	if (_nowEvent == ConnectServer) { return ConnectServer; }
	else if (_nowEvent == SignUp) { return SignUp; }
	else if (_nowEvent == SignIn) { return SignIn; }
	else if (_nowEvent == GetRooms) { return GetRooms; }
	else if (_nowEvent == CreateRoom) { return CreateRoom; }
	else if (_nowEvent == EnterRoom) { return EnterRoom; }
	else if (_nowEvent == Dialog) { return Dialog; }
}

string Connect::getStatus(Status status)
{
	//ConnectServer = 1, //连接服务器事件
	if (status == ConnectServerCase1Failed) { return " "; }
	else if (status == ConnectServerCase1Successful) { return "已与服务器成功建立连接，正在转入登录界面。。。"; }
	else if (status == ConnectServerCase2Failed) { return "正在连接：" + _addr + "\n请稍后，若长时间未正常连接请再尝试进行重连。"; }
	//SignIn = 2, //登录事件
	else if (status == SignInCase1Failed) { return "已与服务器失去连接，请返回服务器连接界面重连。"; }
	else if (status == SignInCase1Successful) { return "连接服务器成功，请登录您的账号，如果没有账号请先注册。"; }
	else if (status == SignInCase2Failed) { return "登录失败，您所输入的ID或用户名为空，请检查您的输入。"; }
	else if (status == SignInCase3Failed) { return "登录失败，您所输入的密码为空，请检查您的输入。"; }
	else if (status == SignInCase4Failed) { return "登录失败，您所输入的用户名或ID不存在。"; }
	else if (status == SignInCase5Failed) { return "登录失败，您所输入的用户名或ID对应多个账户。\n请联系开发维护人员。"; }
	else if (status == SignInCase6Failed) { return "登录失败，服务器在执行查询ID或用户名的SQL语句时出现未知异常。\n请联系开发维护人员。"; }
	else if (status == SignInCase7Failed) { return "登录失败，您所输入的密码错误。"; }
	else if (status == SignInCase7Successful) { return "登录成功，1秒后自动跳转到选择房间界面。"; }
	//SignUp = 3, //注册事件
	else if (status == SignUpCase1Failed) { return "已与服务器失去连接，请返回服务器连接界面重连。"; }
	else if (status == SignUpCase1Successful) { return "连接服务器成功，请输入用户名、昵称和密码进行账号注册。"; }
	else if (status == SignUpCase2Failed) { return "创建账号失败。\n用户名不能为空，请重填。"; }
	else if (status == SignUpCase3Failed) { return "创建账号失败。\n用户名不能全是数字，请重填。"; }
	else if (status == SignUpCase4Failed) { return "创建账号失败。\n昵称不能为空，请重填。"; }
	else if (status == SignUpCase5Failed) { return "创建账号失败。\n密码不能为空，请重填。"; }
	else if (status == SignUpCase6Failed) { return "创建账号失败。\n请重填用户名或昵称，因为您的用户名或昵称已被其他人占用。"; }
	else if (status == SignUpCase7Failed) { return "创建账号失败。\n您输入的信息包含非法字符。\n这是本不应该出现的SQL指令错误，请联系开发维护人员。"; }
	else if (status == SignUpCase8Failed) { return "创建账号失败。\n在正式插入您的账号信息到数据库时遇到未知错误。\n应该是服务器硬盘没空间了，请联系开发维护人员。"; }
	else if (status == SignUpCase8Successful) { return "恭喜您注册成功，请返回登录界面进行登录。\n若您无操作，系统将在3秒钟后帮您自动转入登录界面。"; }
	//GetRooms = 4, //获取房间列表事件
	else if (status == GetRoomsCase1Failed) { return "未定义的状态码"; }
	else if (status == GetRoomsCase1Successful) { return "未定义的状态码"; }
	//CreateRoom = 5, //创建房间事件
	else if (status == CreateRoomCase1Failed) { return "未定义的状态码"; }
	else if (status == CreateRoomCase1Successful) { return "未定义的状态码"; }
	//EnterRoom = 6, //进入房间事件
	else if (status == EnterRoomCase1Failed) { return "未定义的状态码"; }
	else if (status == EnterRoomCase1Successful) { return "未定义的状态码"; }
	//Dialog = 7, //对话事件
	else if (status == DialogCase1Failed) { return "未定义的状态码"; }
	else if (status == DialogCase1Successful) { return "未定义的状态码"; }
}

void Connect::onOpen(WebSocket* ws)
{
	//进行这样的判断是因为WebSocket对象没有setTag方法0
	if (ws != _ws){return;}
	_isConnecting = false;
	if (_nowEvent == ConnectServer) { ConnectServerScene::dealServerResponse(ConnectServerCase1Successful); }
	else if (_nowEvent == SignIn) { SignInScene::dealServerResponse(GetConnectStatus(SignInCase1Successful)); }
	else if (_nowEvent == SignUp) { SignUpScene::dealServerResponse(GetConnectStatus(SignUpCase1Successful)); }
	else if (_nowEvent == GetRooms) { createMsg(); sendMsg(); }
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

void Connect::createMsg()
{
	QJson::emptyDoc();
	addMsg("event", getNowEvent());
}

void Connect::sendMsg()
{
	if (!_ws) { return; }
	_ws->send(QJson::getString());
}

void Connect::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
	if (ws != _ws) { return; }
	CCLOG("收到信息：%s", data.bytes);
	QJson::initDocWithString(data.bytes);
	int event = QJson::getInt("event");
	if (event == 3)
	{
		SignUpScene::dealServerResponse(QJson::getInt("status"));
	}
}