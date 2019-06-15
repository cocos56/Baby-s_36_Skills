#pragma once

#include "QE.h"

class ConnectServerScene : public Layer, public EditBoxDelegate, public NetworkBaseScene
{
	QE_SINGLETON_H(ConnectServerScene);
	QE_CreateSceneFromLayer_H(ConnectServerScene);
	NW_BaseScene;
public:
	static void dealServerResponse(int statusCode);
private:
	static EditBox* _ip1Box, * _ip2Box, * _port1Box, * _port2Box;

	void initLabel();

	void initMenu();

	void back();

	void initEditBox();

	void enterSignInScene(float f);

	void connect(int n);
};