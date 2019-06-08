#pragma once

#include "QE.h"

class SocketIOTestLayer : public Layer, public SocketIO::SIODelegate
{
	QE_CreateSceneFromLayer_H(SocketIOTestLayer);
	QE_SINGLETON_H(SocketIOTestLayer);

public:
	static SIOClient* _sioClient;
	static bool isConnect;
	static string addr;
	static void connect();

	static Label* label, *logLabel;

private:
	void initSocket();
	virtual void onConnect(SIOClient* client);
	virtual void onMessage(SIOClient* client, const string& data);
	virtual void onClose(SIOClient* client);
	virtual void onError(SIOClient* client, const string& data);
	void callClientEvent(SIOClient* client, const string& data);
	void updateStatus(bool status);
	void updateLabel();
};