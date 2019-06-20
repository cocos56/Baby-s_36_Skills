#pragma execution_character_set("utf-8")

#include "Connect.h"

WebSocket* Connect::_ws = nullptr;
bool Connect::_isConnecting = false;
string Connect::_addr = "ws://10.6.32.1:56/";
Connect::Event Connect::_nowEvent;

QE_SINGLETON_CPP(Connect);

void Connect::connect(Event nowEvent){
	_nowEvent = nowEvent;
	if (!_ws) { Connect::getInstance()->initSocket(); return; };
	if (_nowEvent == GetRooms) { createMsg(); sendMsg(); }
}

void Connect::initSocket(){
	_isConnecting = true;
	_ws = new WebSocket();
	if (!_ws->init(*this, _addr)){ CC_SAFE_DELETE(_ws); }
}

//int Connect::getNowEvent(){ return _nowEvent; }

string Connect::getStatus(int statusCode){ return getStatus(Connect::Status(statusCode)); }

string Connect::getStatus(Status status){
	//ConnectServer = 1, //连接服务器事件
	if (status == ConnectServerCase1Successful) { return "已与服务器：" + _addr + " 成功建立连接，马上为您转入登录界面。"; }
	else if (status == ConnectServerCase2Failed) { return "正在连接：" + _addr + "\n请稍后，若长时间未正常连接请再尝试进行重连。"; }
	//SignIn = 2, //登录事件
	else if (status == SignInCase1Successful) { return "请登录您的账号，如果没有账号请先注册。"; }
	else if (status == SignInCase2Failed) { return "登录失败，您所输入的ID或用户名为空，请检查您的输入。"; }
	else if (status == SignInCase3Failed) { return "登录失败，您所输入的密码为空，请检查您的输入。"; }
	else if (status == SignInCase4Failed) { return "登录失败，您所输入的用户名或ID不存在。"; }
	else if (status == SignInCase5Failed) { return "登录失败，您所输入的用户名或ID对应多个账户。\n请联系开发维护人员。"; }
	else if (status == SignInCase6Failed) { return "登录失败，服务器在执行查询ID或用户名的SQL语句时出现未知异常。\n请联系开发维护人员。"; }
	else if (status == SignInCase7Failed) { return "登录失败，您所输入的密码错误。"; }
	else if (status == SignInCase7Successful) { return "登录成功，马上为您转到选择房间界面。"; }
	//SignUp = 3, //注册事件
	else if (status == SignUpCase1Successful) { return "请输入用户名、昵称和密码进行账号注册。"; }
	else if (status == SignUpCase2Failed) { return "创建账号失败。\n用户名不能为空，请重填。"; }
	else if (status == SignUpCase3Failed) { return "创建账号失败。\n用户名不能全是数字，请重填。"; }
	else if (status == SignUpCase4Failed) { return "创建账号失败。\n昵称不能为空，请重填。"; }
	else if (status == SignUpCase5Failed) { return "创建账号失败。\n密码不能为空，请重填。"; }
	else if (status == SignUpCase6Failed) { return "创建账号失败。\n请重填用户名或昵称，因为您的用户名或昵称已被其他人占用。"; }
	else if (status == SignUpCase7Failed) { return "创建账号失败。\n您输入的信息包含非法字符。\n这是本不应该出现的SQL指令错误，请联系开发维护人员。"; }
	else if (status == SignUpCase8Failed) { return "创建账号失败。\n在正式插入您的账号信息到数据库时遇到未知错误。\n应该是服务器硬盘没空间了，请联系开发维护人员。"; }
	else if (status == SignUpCase8Successful) { return "恭喜您注册成功。\n马上为您转入登录界面。"; }
	//GetRooms = 4, //获取房间列表事件
	else if (status == GetRoomsCase1Successful) { return "请加入房间。"; }
	else if (status == GetRoomsCase2Failed) { return "请创建房间。"; }
	//CreateRoom = 5, //创建房间事件
	else if (status == CreateRoomCase1Successful) { return ""; }//{ return "请输入您所要创建房间的名称和密码"; }
	else if (status == CreateRoomCase2Failed) { return "创建房间失败。\n房间名不能为空，请重填。"; }
	else if (status == CreateRoomCase3Failed) { return "创建房间失败。\n服务器可承载的房间数量已达上限，请选择加入房间。"; }
	else if (status == CreateRoomCase3Successful) { return "恭喜您创建房间成功。\n马上为您转入选择角色界面。"; }
	//JoinRoom = 6, //进入房间事件
	else if (status == JoinRoomCase1Successful) { return"";/*"请输入您所要加入房间的名称和密码"; */}
	else if (status == JoinRoomCase2Failed) { return "进入房间失败，房间名为空"; }
	else if (status == JoinRoomCase3Failed) { return "进入房间失败，房间密码错误"; }
	else if (status == JoinRoomCase3Successful) { return "进入房间成功"; }
	//SelectRole = 7, //选择角色事件
	else if (status == SelectRoleCase1Successful) { return "请选择您要扮演的角色。"; }
	else if (status == SelectRoleCase2Failed) { return "您未选择角色，请选择您要扮演的角色。"; }
	else if (status == SelectRoleCase3Failed) { return "所选的角色已被其他玩家选择，请重新选择您要扮演的角色。"; }
	else if (status == SelectRoleCase3Successful) { return "恭喜您成功选择此角色"; }
	//Waiting = 8, //等待所有玩家就绪事件
	else if (status == WaitingCase1Successful) { return "";/* "请等待其他玩家就绪。"; */}
	else if (status == WaitingCase2Failed) { return "宝宝玩家已离开。"; }
	else if (status == WaitingCase2Successful) { return "宝宝玩家已加入。"; }
	else if (status == WaitingCase3Failed) { return "坏人玩家已离开。"; }
	else if (status == WaitingCase3Successful) { return "坏人玩家已加入。"; }
	else if (status == WaitingCase4Failed) { return "裁判玩家已离开。"; }
	else if (status == WaitingCase4Successful) { return "裁判玩家已加入。"; }
	//Dialog = 9, //对话事件
	else if (status == DialogCase1Successful) { return "";/*"请发言"; */}
}

void Connect::onOpen(WebSocket* ws)
{
	//进行这样的判断是因为WebSocket对象没有setTag方法
	if (ws != _ws){return;}
	_isConnecting = false;
	if (Connect::_nowEvent != Connect::Event::ConnectServer) { return; };
	ConnectServerScene::dealServerResponse(111);
}

void Connect::onClose(WebSocket* ws)
{
	if (ws != _ws) { return; }
	_ws = nullptr;
	_isConnecting = false;

	ConnectServerScene::disConnect();
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
	CCLOG("send：%s", QJson::getString().c_str());
	_ws->send(QJson::getString());
}

void Connect::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
	if (ws != _ws) { return; }
	CCLOG("收到信息：%s", data.bytes);
	QJson::initDocWithString(data.bytes);
	int event = QJson::getInt("event");
	if (event == 2) { SignInScene::dealServerResponse(QJson::getInt("status")); }
	else if (event == 3){ SignUpScene::dealServerResponse(QJson::getInt("status")); }
	else if (event == 4) { GetRoomsScene::dealServerResponse(QJson::getInt("status")); }
	else if (event == 5){ CreateRoomScene::dealServerResponse(QJson::getInt("status")); }
	else if (event == 6) { JoinRoomScene::dealServerResponse(QJson::getInt("status")); }
	else if (event == 7) { SelectRoleScene::dealServerResponse(QJson::getInt("status")); }
	else if (event == 8 || event == 9) {
		NetworkGameScene::dealServerResponse(QJson::getInt("status"));
		WaitingNetworkGameScene::dealServerResponse(QJson::getInt("status"));
	}
}