#pragma execution_character_set("utf-8")

#include "QString.h"

int QString::getStringLetterNumber(string str, CharSet cs)
{
	if (cs != UTF_8)
	{
		return -1;
	}
	const char* s = str.c_str();
	int i = 0, j = 0;
	while (s[i])
	{
		if ((s[i] & 0xc0) != 0x80) j++;
		i++;
	}
	return j;
}

vector<string> QString::strToVector(string str, CharSet cs)
{
	vector<string> vstr;
	if (cs != UTF_8)
	{
		return vstr;
	}

	const char* s = str.c_str();
	int i = 0, j = 0;
	while (1)
	{
		if (!s[i])
		{
			break;
		}
		i++;
		CCLOG("c = %d", s[i]);
		if ((s[i] & 0xc0) != 0x80)
		{
			CCLOG("%s", str.substr(j, i).c_str());
			vstr.push_back(str.substr(j, i));
			//i++;
			j = i;
		}
		else
		{
			//i++;
		}
	}
	return vstr;
}