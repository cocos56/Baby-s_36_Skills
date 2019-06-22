#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class Connect : public WebSocket::Delegate{
	QE_SINGLETON_H(Connect);
public:
	enum Event {
		//编码规范：用一个数字编码可能出现的所有事件
		ConnectServer = 1, //连接服务器事件
		SignIn = 2, //登录事件
		SignUp = 3, //注册事件
		GetRooms = 4, //获取房间列表事件
		CreateRoom = 5, //创建房间事件
		JoinRoom = 6, //加入房间事件
		SelectRole = 7, //选择角色事件
		Waiting = 8, //等待所有玩家就绪事件
		Dialog = 9, //对话事件
	};

	enum Status {
		//编码规范：用三个数字编码可能出现的所有状态，第一个数字代表事件类型，第二个数字代表造成该事件成功或失败的原因/情形/情况种类，第三个数字代表事件最终状态：0代表失败，1代表成功。
		ConnectServerCase1Successful = 111, //连接服务器成功，成功原因：成功建立WebSocket
		ConnectServerCase2Failed = 120, //连接服务器错误，错误原因：已经在建立WebSocket过程中，请耐心等待响应结果
		ConnectServerCase3Failed = 130, //连接服务器错误，错误原因：在其他界面与服务器断开连接
		//SignIn = 2, //登录事件
		SignInCase1Successful = 211, //连接服务器成功，成功原因：成功建立WebSocket
		SignInCase2Failed = 220, //ID或用户名为空
		SignInCase3Failed = 230, //密码为空
		SignInCase4Failed = 240, //用户名或ID不存在
		SignInCase5Failed = 250, //用户名或ID对应多个账户
		SignInCase6Failed = 260, //执行查询ID或用户名的SQL语句时出现未知异常
		SignInCase7Failed = 270, //密码错误
		SignInCase7Successful = 271, //登录成功

		//SignUp = 3, //注册事件
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
		GetRoomsCase1Successful = 411, //连接服务器成功，成功原因：成功建立WebSocket，请加入房间。
		GetRoomsCase2Failed = 420, //请创建房间。
		//CreateRoom = 5, //创建房间事件
		CreateRoomCase1Successful = 511, //连接服务器成功，成功原因：成功建立WebSocket，请输入您所要创建房间的名称和密码
		CreateRoomCase2Failed = 520, //创建房间失败，房间名不能为空，请重填。
		CreateRoomCase3Failed = 530, //创建房间失败。\n在正式插入您的账号信息到数据库时遇到未知错误。\n应该是服务器硬盘没空间了，请联系开发维护人员。
		CreateRoomCase3Successful = 531, //恭喜您创建房间成功。\n马上为您转入选择角色界面。
		//JoinRoom = 6, //进入房间事件
		JoinRoomCase1Successful = 611, //连接服务器成功，成功原因：成功建立WebSocket，请输入您所要加入房间的名称和密码
		JoinRoomCase2Failed = 620, //进入房间失败，房间名为空
		JoinRoomCase3Failed = 630, //进入房间失败，房间密码错误
		JoinRoomCase3Successful = 631, //进入房间成功
		//SelectRole = 7, //选择角色事件
		SelectRoleCase1Successful = 711, //此状态为默认在连接服务器成功的情况下，即使正在建立WebSocket
		SelectRoleCase2Failed = 720, //该玩家未选择角色
		SelectRoleCase3Failed = 730, //该玩家所选的角色已被其他玩家选择
		SelectRoleCase3Successful = 731, //该玩家成功选择角色
		//Waiting = 8, //等待所有玩家就绪事件
		WaitingCase1Successful = 811, //此状态为默认在连接服务器成功的情况下，即使正在建立WebSocket
		WaitingCase2Failed = 820, //宝宝玩家已离开
		WaitingCase2Successful = 821, //宝宝玩家已加入
		WaitingCase3Failed = 830, //坏人玩家已离开
		WaitingCase3Successful = 831, //坏人玩家已加入
		WaitingCase4Failed = 840, //裁判玩家已离开
		WaitingCase4Successful = 841, //裁判玩家已加入
		//Dialog = 9, //对话事件
		DialogCase1Successful = 911, //连接服务器成功，成功原因：成功建立WebSocket	
		DialogCase2Successful = 921, //轮到坏人玩家发言
		DialogCase3Successful = 931, //轮到宝宝玩家发言
		DialogCase4Successful = 941, //轮到裁判玩家发言
		DialogCase5Successful = 951, //裁判玩家已判决本轮游戏，本轮游戏结束
		DialogCase6Successful = 961, //坏人玩家发言了
		DialogCase7Successful = 971, //宝宝玩家发言了
		DialogCase8Successful = 981, //裁判玩家发言了
	};

public:
	static int getNowEvent() { return _nowEvent; } ;
	static string getStatus(Status status);
	static string getStatus(int statusCode);
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