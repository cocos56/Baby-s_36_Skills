#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine.h"

/*
Quick Engine所属快速TMX模块
含：
1.QTMX类
用途：用于快速管理TMX文件，主要用于从TMX文件中解析坐标
*/

class QTMX
{
public:
	static void initCoordinatesByTMXFile(vector<Coordinate>& coordinates,const string& fileName, const string& objectGroupName);
	static void initCoordinatesByTMXFile(Coordinate& coordinate, const string& fileName, const string& objectGroupName);
};

