#pragma once

/*
Quick Engine模块

QE V2.0 for Baby's_36_Skills

QE（Quick Engine，快速引擎）简介：
基于Cocos2d-x 3.17.1、C++ 17构建，用来尽可能多地提升代码的复用性。
QE具体表现为：优化默认的参数值及参数列表，使原来需要数行代码才能完成的功能，现在只需要一行代码就能完成。

比如：
1.快速生成背景精灵、设置锚点和位置均为（0, 0）、并添加到当前节点，只需要调用一个宏就行了。
	记得把资源改成bg.png。
	调用“QE_addBgSpriteToThis”这个宏即可，无需多于代码，也不需要传递任何参数

2.快速生成菜单，传两张图片的名以及一个可调用对象即可。

3.所有头文件只需要在这里包含一下，然后在相应的头文件中再包含一下此头文件就可以了。
这种你中有我，我中有你的设计效果可以大大减少包含的头文件数量。
*/

//宏
//CB = callback
#define QE_CB0(Type, Fun, ...) std::bind(&Type::Fun,this, ##__VA_ARGS__)
//CBWT = callback with target
#define QE_CBWT0(Type, Fun, targert, ...) std::bind(&Type::Fun,targert, ##__VA_ARGS__)
//#define CC_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define QE_CALLBACK_1(Type,Fun) CC_CALLBACK_1(Type::Fun, this)

//C++
using namespace std;

//Cocos2d-x
#include "cocos2d.h"
USING_NS_CC;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
#include "network/SocketIO.h"
using namespace cocos2d::network;

//设计模式
#include "QE/QDesignMode.h"

//QE
#include "QE/QType.h"
#include "QE/QScene.h"
#include "QE/QLayer.h"
#include "QE/QMenu.h"
#include "QE/QSprite.h"
#include "QE/QFileUtils.h"
#include "QE/QAnimate.h"
#include "QE/QObject.h"
#include "QE/QJson.h"
#include "QE/QTMX.h"

//User
#include "AppDelegate.h"
#include "HelloWorldScene.h"
