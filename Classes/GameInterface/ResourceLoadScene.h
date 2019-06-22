#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class ResourceLoadScene : public Layer
{
public:
	static Scene * createScene();//创建场景（静态的类方法）
    virtual bool init();//构造函数（继承自父类，virtual虚函数）

	//创建layer（宏定义。里面传的参数是当前的类名）
	CREATE_FUNC(ResourceLoadScene);
	
	void startScene();
};