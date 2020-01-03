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
	static string _name, _creator;
private:
	//标签相关
	static Label * _roomName, * _roomCreator;
	void initLabel();

	//菜单相关
	void initMenu();
	//菜单按钮回调函数相关
	void createRoom();
	void joinRoom();
	void back();

	//
	virtual void onEnterTransitionDidFinish() ;
};