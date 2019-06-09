#pragma once
# pragma execution_character_set("utf-8")

#include "QE.h"

class Connect : public WebSocket::Delegate
{
	QE_SINGLETON_H(Connect);

public:
	
	static bool _isConnecting;
	static WebSocket* _ws;
	static string _addr, _nowEvent;

	static void connect();
	static void createMsg();
	static void addMsg(JString key, JString value);
	static void sendMsg();


private:
	void initSocket();

	//委托协议方法
	virtual void onOpen(WebSocket* ws) noexcept override;
	virtual void onMessage(WebSocket* ws, const WebSocket::Data& data) noexcept override;
	virtual void onClose(WebSocket* ws) noexcept override;
	virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error) noexcept override;
};