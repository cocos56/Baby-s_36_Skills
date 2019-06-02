#pragma once

/*
Quick Engine所属基本数据类型模块
含：
1.Coordinate类
用途：用于管理坐标
*/


class Coordinate
{
public:
	Coordinate(int num, int x, int y) : num(num), x(x), y(y) {};
	Coordinate(int x, int y) : num(0), x(x), y(y) {};
	Coordinate() : num(-1), x(-1), y(-1) {};

	int num, x, y;
};

#include "QE.h"