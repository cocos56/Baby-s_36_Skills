#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class NetworkScene
{
public:
	//处理服务器相应的数据
	static void dealServerResponse();
	static void dealServerResponse(string str);

	//服务器返回信息相关
	static Label * _logLabel;

	//标签相关
	void initLabel() {};
	void createLabel(string show) ;

	//菜单相关
	void initMenu() {};

	//输入框相关
	EditBox* createEditBox(string normalPngFile, EditBoxDelegate* delegate);

protected:
	static Label* _label;
};