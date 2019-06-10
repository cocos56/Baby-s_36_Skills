#pragma once

/*
Quick Engine所属快速文件使用模块
用途：用于快速设置资源搜索路径
*/

#include "QE.h"

#define QE_SetResourcesSearchDir \
CCASSERT(paths.size(), "paths.size should not = 0"); \
FileUtils::getInstance()->setSearchResolutionsOrder(paths);