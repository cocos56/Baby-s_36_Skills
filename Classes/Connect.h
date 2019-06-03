#pragma once

#include "QE.h"

class Connect : public SocketIO::SIODelegate
{
	QE_SINGLETON_H(Connect);

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
};