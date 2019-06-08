#pragma once

#include "QE.h"

class Connect : public WebSocket::Delegate
{
	QE_SINGLETON_H(Connect);

public:
	
	static bool _isConnecting;
	static void connect();
	static WebSocket* _ws;
	static string _addr;

private:
	void initSocket();

	virtual void onOpen(cocos2d::network::WebSocket* ws);

	virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);

	virtual void onClose(cocos2d::network::WebSocket* ws);

	virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
};