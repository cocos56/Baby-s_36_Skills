#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class SelectRoleScene : public Layer, public EditBoxDelegate, public NetworkBaseScene
{
	QE_SINGLETON_H(SelectRoleScene);
	QE_CreateSceneFromLayer_H(SelectRoleScene);
	NW_BaseScene;
public:
	static void dealServerResponse(int statusCode);
	static int _index;
private:
	//背景精灵相关
	void initSprits();

	//标签相关
	void initLabel();

	//菜单相关
	void initMenu();
	//菜单按钮回调函数相关
	void confirm();
	void back();

	//选项
	static RadioButtonGroup* _radioButtonGroup;
	void initRadioButton();
	void onChangedRadioButtonGroup(RadioButton* radioButton, int index, RadioButtonGroup::EventType type);
};