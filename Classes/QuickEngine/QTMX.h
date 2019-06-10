#pragma once

/*
Quick Engine所属快速TMX模块
含：
1.QTMX类
用途：用于快速管理TMX文件，主要用于从TMX文件中解析坐标
*/

#include "QE.h"

class QTMX
{
public:
	static void initCoordinatesByTMXFile(vector<Coordinate>& coordinates,const string& fileName, const string& objectGroupName);
	static void initCoordinatesByTMXFile(Coordinate& coordinate, const string& fileName, const string& objectGroupName);
};

