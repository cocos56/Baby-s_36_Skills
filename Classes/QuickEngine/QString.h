#pragma execution_character_set("utf-8")
/*开头第一句主要是为了完美解决C++ VS输出中文乱码痛点
概要：
使用高版本的VS，将源代码文件保存为utf-8格式，接着在源码开头处告诉编译器要用utf-8编码方案进行解析源代码。
这样做直接就可以了正常解析源码中的中文了，无需使用xml文档或者对源码中的中文字符进行额外的转码处理。
具体参考：https://blog.csdn.net/COCO56/article/details/91350176
*/
#pragma once

#include "QuickEngine.h"

/*QuickEngine为我自主开发的游戏引擎
// #include "QuickEngine.h"
// QString是QuickEngine中的一个模块，用于帮助其他开发者处理快速字符串相关的事件
*/

//#include <vector>
//#include <string>
//using namespace std;

class QString
{
	enum CharSet
	{
		UTF_8 = 0
	};
public:
	/*暂时不处理非UTF_8编码的处理*/
	//获取一个字符串中有多少个字符
	static int getStringLetterNumber(string str, CharSet cs = UTF_8);
	//将一个字符串中的所有字符都识别分离出来，并将每个字符保存为vector<string>中的一个元素
	static vector<string> strToVector(string str, CharSet cs = UTF_8);
};