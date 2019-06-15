#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class GetRoomsScene : public Layer, public EditBoxDelegate, public NetworkBaseScene
{
	QE_SINGLETON_H(GetRoomsScene);
	QE_CreateSceneFromLayer_H(GetRoomsScene);
	NW_BaseScene;
public:
	static void dealServerResponse(int statusCode);
private:
	void enterSignInScene(float f);
	//标签相关
	static Label* _roomID, * _roomName, * _roomCreater;
	void initLabel();

	//菜单相关
	void initMenu();
	//菜单按钮回调函数相关
	void createRoom();
	void joinRoom();
	void back();
};