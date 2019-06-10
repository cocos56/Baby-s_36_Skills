#pragma execution_character_set("utf-8")
#pragma once

/*
Quick Engine所属快速层模块
用途：用于快速创建Layer的子类，并进行相应的初始化。
*/

#define QE_CreateLayerFromLayer_H(TYPE) \
public: \
	CREATE_FUNC(TYPE); \
	virtual bool init(); \
	QE_get_winSize;

#define QE_CreateLayerFromLayer_CPP(TYPE) \
bool TYPE::init() \
{ \
	if (!Layer::init()) \
	{ \
		return false; \
	}
