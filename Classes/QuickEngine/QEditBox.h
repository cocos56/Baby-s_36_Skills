#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine.h"

class QEditBox
{
	//输入框相关
public:
	static EditBox* createEditBox(string normalPngFile, EditBoxDelegate* delegate);
};