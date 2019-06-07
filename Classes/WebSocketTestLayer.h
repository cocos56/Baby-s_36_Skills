#pragma once

#include "QE.h"

class WebSocketTestLayer : public Layer, public WebSocket::Delegate
{
	QE_CreateSceneFromLayer_H(WebSocketTestLayer);

	static LabelTTF* label;
	static int _sendTextTimes;
	WebSocket* _wsiSendText;

	void initMenu();

	void sendMsg();

	virtual void onOpen(cocos2d::network::WebSocket* ws);

	virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);

	virtual void onClose(cocos2d::network::WebSocket* ws);

	virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
};