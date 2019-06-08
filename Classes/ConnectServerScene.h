#pragma once

#include "QE.h"

class ConnectServerScene : public Layer, public EditBoxDelegate
{
	QE_CreateSceneFromLayer_H(ConnectServerScene);

private:
	static EditBox* _ip1Box, * _ip2Box, * _port1Box, * _port2Box;
	static Label* _logLabel;

	void initLabel();
	Label* createLabel(string text);

	void initMenu();

	void initEditBox();

	void connect(int n);

	EditBox* createEditBox(string normalPngFile, string text, int maxLength) ;
	virtual void editBoxReturn(EditBox* editBox) {};
};