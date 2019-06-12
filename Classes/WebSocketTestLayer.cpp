#pragma execution_character_set("utf-8")

#include "WebSocketTestLayer.h"

Label* WebSocketTestLayer::label;
int WebSocketTestLayer::_sendTextTimes = 0;

QE_CreateSceneFromLayer_CPP(WebSocketTestLayer);
	//初始化菜单
	initMenu();

	label = Label::create("", "Marker Felt.ttf", 24);
	label->setAnchorPoint(Vec2(0, 0));
	label->setPosition(10, 300);
	addChild(label);

	label->setString("initWeb");

	_wsiSendText = new WebSocket();
	string aim = "ws://echo.websocket.org";
	aim = "ws://10.6.32.1";
	aim = "ws://10.6.32.1:80";
	aim = "ws://10.6.32.1:56";
	_wsiSendText->init(*this, aim);

	return true;
}

void WebSocketTestLayer::initMenu()
{
	label = Label::create("Send msg", "Marker Felt.ttf", 25);
	MenuItemLabel* sendMsgItem = MenuItemLabel::create(label, bind(&WebSocketTestLayer::sendMsg, this));
	sendMsgItem->setPosition(410, 200);

	Menu* mn = Menu::create(sendMsgItem, NULL);
	mn->setPosition(0, 0);
	addChild(mn);
}

void WebSocketTestLayer::sendMsg()
{
	_wsiSendText->send("Hello, I am Cocos2d-x");
}

void WebSocketTestLayer::onOpen(WebSocket* ws)
{
	if (ws == _wsiSendText)
	{
		label->setString("Send Text WS was opened.");
	}
	//label->setString("onOpen");
}

void WebSocketTestLayer::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
	if (!data.isBinary)
	{
		_sendTextTimes++;
		char times[100] = { 0 };
		sprintf(times, "%d", _sendTextTimes);
		std::string textStr = std::string("response text msg: ") + data.bytes + ", " + times;
		CCLOG("%s", textStr.c_str());
		label->setString(textStr.c_str());
	}
}

void WebSocketTestLayer::onClose(network::WebSocket* ws)
{
	if (ws == _wsiSendText)
	{
		_wsiSendText = NULL;
	}
	CC_SAFE_DELETE(ws);
}

void WebSocketTestLayer::onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error)
{
	CCLOG("Error was fired, error code: %d", error);
	if (ws == _wsiSendText)
	{
		char buf[100] = { 0 };
		sprintf(buf, "an error was fired, code: %d", error);
		label->setString(buf);
	}
}

