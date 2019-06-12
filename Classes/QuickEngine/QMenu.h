#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine.h"

/*
Quick Engine所属快速菜单模块
含：
1.QMenu类
用途：用于快速创建菜单
*/

class QMenu
{
	QE_SINGLETON_H(QMenu);

public:
	static MenuItemSprite* createMenuItemSprite(const string& picture, const ccMenuCallback& callback, int x=0, int y = 10);
	static MenuItemSprite* createMenuItemSprite(const string& normal_picture, const string& pressed_picture, const ccMenuCallback& callback, int x = 0, int y = 10);

	static MenuItemLabel* createMenuItemLabel(const string& text, const ccMenuCallback& callback);
	
	static Menu* createMenuLabel(const string& text, const ccMenuCallback& callback);
	static Menu* createMenuSprite(const string& picture, const ccMenuCallback& callback);
	static Menu* createMenuSprite(const string& picture, const ccMenuCallback& callback, MenuItem *&item);

	static void releaseMenuItemVector(vector<MenuItem*>& menuItems);
};

#define QE_CreateLabelMenuAgain(__X__ , __Y__ ,__STR__, __TYPE__, __Fun__, ...) menu = QMenu::createMenuLabel(__STR__, bind(&__TYPE__::__Fun__, this, ##__VA_ARGS__)); \
menu->setPosition(__X__, __Y__); \
addChild(menu); \

#define QE_CreateLabelMenu(__X__ , __Y__ ,__STR__, __TYPE__, __Fun__, ...) Menu* menu; \
QE_CreateLabelMenuAgain(__X__ , __Y__ ,__STR__, __TYPE__, __Fun__, ##__VA_ARGS__)

#define QE_addMenuTo(target) Menu* \
menu = Menu::createWithArray(items); \
menu->setAnchorPoint(Vec2(0, 0)); \
menu->setPosition(0, 0); \
target->addChild(menu); \
items.clear();

#define QE_addMenuToThis Menu* \
menu = Menu::createWithArray(items); \
menu->setAnchorPoint(Vec2(0, 0)); \
menu->setPosition(0, 0); \
addChild(menu); \
items.clear();

#define QE_addMenuToThisAgainWithPriority(_priority) \
menu = Menu::createWithArray(items); \
menu->setAnchorPoint(Vec2(0, 0)); \
menu->setPosition(0, 0); \
addChild(menu, _priority); \
items.clear();