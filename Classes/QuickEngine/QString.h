#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine.h"

class QString
{
	enum CharSet
	{
		UTF_8 = 0
	};
public:
	//暂时不处理非UTF_8编码的处理
	static int getStringLetterNumber(string str, CharSet cs = UTF_8);
	static vector<string> strToVector(string str, CharSet cs = UTF_8);
};