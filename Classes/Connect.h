#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

#define ConnectStatus(__CASE__) Connect::getStatus(Connect::Status::__CASE__)

class Connect : public WebSocket::Delegate
{
	QE_SINGLETON_H(Connect);

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
		//SignUp = 3, //注册事件
		SignUpCase1Failed = 310, //连接服务器错误，错误原因：关闭WebSocket
		SignUpCase1Successful = 311, //连接服务器成功，成功原因：成功建立WebSocket
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
	static string getNowEvent();
	static string getStatus(Status status);
	static bool _isConnecting;
	static WebSocket* _ws;
	static string _addr;
	static Event _nowEvent;

	static void connect(Event nowEvent);
	static void createMsg();
	static void addMsg(JString key, JString value);
	static void sendMsg();

private:
	void initSocket();

	//委托协议方法
	virtual void onOpen(WebSocket* ws) override;
	virtual void onMessage(WebSocket* ws, const WebSocket::Data& data) override;
	virtual void onClose(WebSocket* ws) override;
	virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error) override;
};