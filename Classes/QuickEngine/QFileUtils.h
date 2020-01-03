#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine.h"

/*
Quick Engine所属快速文件使用模块
用途：用于快速设置资源搜索路径
*/

#define QE_SetResourcesSearchDir \
CCASSERT(paths.size(), "paths.size should not = 0"); \
FileUtils::getInstance()->setSearchResolutionsOrder(paths);