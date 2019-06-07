#pragma once

#include "QE.h"

class SocketIOTest : public cocos2d::network::SocketIO::SIODelegate
{
	QE_SINGLETON_H(SocketIOTest);

public:
	static SIOClient* _sioClient;
	static bool isConnect;
	static string addr;
	static void connect();

private:
	void initSocket();
	virtual void onConnect(SIOClient* client);
	virtual void onMessage(SIOClient* client, const string& data);
	virtual void onClose(SIOClient* client);
	virtual void onError(SIOClient* client, const string& data);
	void callClientEvent(SIOClient* client, const string& data);
	void updateStatus(bool status);
};