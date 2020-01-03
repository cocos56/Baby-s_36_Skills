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
		if ((s[i] & 0b11000000) != 0b10000000) j++;
		i++;
	}
	return j;
}

vector<string> QString::strToVector(string str, CharSet cs)
{
	vector<string> vstr;
	if (cs != UTF_8) { return vstr; };

	const char* s = str.c_str();
	int i = 1, j = 0, l=0, sum=0;

	while (1)
	{
		if (s[i])//未到字符串的结尾，即未读取到'\0'
		{
			if ((s[i] & 0b11000000) != 0b10000000)//读取到一个新字符的开头
			{
				l = i - j;
				//CCLOG("f = %d, j=%d, l=%d, s=%s", flag, j, l, str.substr(j, l).c_str());
				vstr.push_back(str.substr(j, l));
				j = i;
			}
			i++;
		}
		else
		{
			l = i - j;
			vstr.push_back(str.substr(j, l));
			break;
		}
	}
	return vstr;
}