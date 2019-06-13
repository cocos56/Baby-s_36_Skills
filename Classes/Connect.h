#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

#define GetConnectStatus(__STATUS__) Connect::getStatus(Connect::Status::__STATUS__)
#define GetConnectStatusByCode(__CODE__) Connect::getStatus(Connect::Status(__CODE__))

class Connect : public WebSocket::Delegate
{
	QE_SINGLETON_H(Connect);
public:
	enum Event {
		//编码规范：用一个数字编码可能出现的所有事件
		ConnectServer = 1, //连接服务器事件
		SignIn = 2, //登录事件
		SignUp = 3, //注册事件
		GetRooms = 4, //获取房间列表事件
		CreateRoom = 5, //创建房间事件
		EnterRoom = 6, //进入房间事件
		Dialog = 7, //对话事件
	};

	enum Status {
		//编码规范：用三个数字编码可能出现的所有状态，第一个数字代表事件类型，第二个数字代表造成该事件成功或失败的原因/情形种类，第三个数字代表事件最终状态：0代表失败，1代表成功。
		//ConnectServer = 1, //连接服务器事件
		ConnectServerCase1Failed = 110, //连接服务器错误，错误原因：关闭WebSocket
		ConnectServerCase1Successful = 111, //连接服务器成功，成功原因：成功建立WebSocket
		ConnectServerCase2Failed = 120, //连接服务器错误，错误原因：已经在建立WebSocket过程中，请耐心等待响应结果
		//SignIn = 2, //登录事件
		SignInCase1Failed = 210, //连接服务器错误，错误原因：关闭WebSocket
		SignInCase1Successful = 211, //连接服务器成功，成功原因：成功建立WebSocket
		SignInCase2Failed = 220, //ID或用户名为空
		SignInCase3Failed = 230, //密码为空
		SignInCase4Failed = 240, //用户名或ID不存在
		SignInCase5Failed = 250, //用户名或ID对应多个账户
		SignInCase6Failed = 260, //执行查询ID或用户名的SQL语句时出现未知异常
		SignInCase7Failed = 270, //密码错误
		SignInCase7Successful = 271, //登录成功

		//SignUp = 3, //注册事件
		SignUpCase1Failed = 310, //连接服务器错误，错误原因：关闭WebSocket
		SignUpCase1Successful = 311, //连接服务器成功，成功原因：成功建立WebSocket
		SignUpCase2Failed = 320, //创建账号失败，用户名不能为空，请重填。
		SignUpCase3Failed = 330, //创建账号失败，用户名不能全是数字，请重填。
		SignUpCase4Failed = 340, //创建账号失败，昵称不能为空，请重填。
		SignUpCase5Failed = 350, //创建账号失败，密码不能为空，请重填。
		SignUpCase6Failed = 360, //创建账号失败，请重填用户名或昵称，因为您的用户名或昵称已被其他人占用。
		SignUpCase7Failed = 370, //创建账号失败，您输入的信息包含非法字符，这是本不应该出现的SQL指令错误，请联系开发维护人员。
		SignUpCase8Failed = 380, //创建账号失败，在正式插入您的账号信息到数据库时遇到未知错误，这种错误理论上很难碰到，请联系开发维护人员。
		SignUpCase8Successful = 381, //创建账号成功，恭喜您注册成功，请返回登录。
		//GetRooms = 4, //获取房间列表事件
		GetRoomsCase1Failed = 410, //连接服务器错误，错误原因：关闭WebSocket
		GetRoomsCase1Successful = 411, //连接服务器成功，成功原因：成功建立WebSocket
		//CreateRoom = 5, //创建房间事件
		CreateRoomCase1Failed = 510, //连接服务器错误，错误原因：关闭WebSocket
		CreateRoomCase1Successful = 511, //连接服务器成功，成功原因：成功建立WebSocket
		//EnterRoom = 6, //进入房间事件
		EnterRoomCase1Failed = 610, //连接服务器错误，错误原因：关闭WebSocket
		EnterRoomCase1Successful = 611, //连接服务器成功，成功原因：成功建立WebSocket
		//Dialog = 7, //对话事件
		DialogCase1Failed = 710, //连接服务器错误，错误原因：关闭WebSocket
		DialogCase1Successful = 711, //连接服务器成功，成功原因：成功建立WebSocket
	};

public:
	static int getNowEvent();
	static string getStatus(Status status);
	static bool _isConnecting;
	static WebSocket* _ws;
	static string _addr;
	static Event _nowEvent;

	static void connect(Event nowEvent);
	static void createMsg();
	static void addMsg(JString key, JString value) { QJson::addMember(key, value); };
	static void addMsg(JString key, int value) { QJson::addMember(key, value); };
	static void sendMsg();

private:
	void initSocket();

	//委托协议方法
	virtual void onOpen(WebSocket* ws) override;
	virtual void onMessage(WebSocket* ws, const WebSocket::Data& data) override;
	virtual void onClose(WebSocket* ws) override;
	virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error) override;
};