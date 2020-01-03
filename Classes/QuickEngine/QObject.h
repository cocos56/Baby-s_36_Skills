#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine.h"

/*
Quick Engine所属快速对象模块
含：
1.QObject类
用途：用于快速管理对象
*/

class QObject
{
public:
	template<class T>
	static void releaseVector(vector<T*>& vec)
	{
		for (size_t i = 0, length = vec.size(); i < length; i++)
		{
			delete vec.at(i);
		}
		vec.clear();
	}
};