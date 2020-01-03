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
	static MenuItem* _item;
	static Menu* _menu;
	static MenuItemSprite* createMenuItemSprite(const string& picture, const ccMenuCallback& callback, int x=0, int y = 10);
	static MenuItemSprite* createMenuItemSprite(const string& normal_picture, const string& pressed_picture, const ccMenuCallback& callback, int x = 0, int y = 10);

	static MenuItemLabel* createMenuItemLabel(const string& text, const ccMenuCallback& callback);
	
	static Menu* createMenuLabel(const string& text, const ccMenuCallback& callback);
	static Menu* createMenuSprite(const string& picture, const ccMenuCallback& callback);
	static Menu* createMenuSprite(const string& picture, const string& pressedPicture, const ccMenuCallback& callback, MenuItem*& item);
	static Menu* createMenuSprite(const string& picture, const string& pressedPicture, const ccMenuCallback& callback);
	static Menu* createMenuSprite(const string& picture, const ccMenuCallback& callback, MenuItem *&item);

	static void releaseMenuItemVector(vector<MenuItem*>& menuItems);
};

#define QE_CreateLabelMenu(__X__ , __Y__ ,__STR__, __TYPE__, __Fun__, ...) QMenu::_menu = QMenu::createMenuLabel(__STR__, bind(&__TYPE__::__Fun__, this, ##__VA_ARGS__)); \
QMenu::_menu->setPosition(__X__, __Y__); \
addChild(QMenu::_menu);

#define QE_CreateSpriteMenu2(__X__ , __Y__ ,__NormalPicture__, __PressedPicture__, __TYPE__, __Fun__, ...) 	QMenu::_menu = QMenu::createMenuSprite(__NormalPicture__, __PressedPicture__, bind(&__TYPE__::__Fun__, this, ##__VA_ARGS__)); \
QMenu::_menu->setPosition(__X__, __Y__); \
addChild(QMenu::_menu);

#define QE_CreateSpriteMenu(__X__ , __Y__ ,__PictureName__, __TYPE__, __Fun__, ...) \
QE_CreateSpriteMenu2(__X__, __Y__, __PictureName__, __PictureName__, __TYPE__, __Fun__, ##__VA_ARGS__)


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