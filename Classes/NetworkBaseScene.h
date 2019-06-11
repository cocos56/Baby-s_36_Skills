#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class NetworkBaseScene
{
public:
	//服务器返回信息相关
	static Label * _logLabel;

	//标签相关
	void initLabel() {};

	//菜单相关
	void initMenu() {};

protected:
	static Label* _label;
};

#define NW_BaseScene public: \
static void dealServerResponse() { dealServerResponse(QJson::getString("消息")); }; \
static void dealServerResponse(string str) { _logLabel->setString(str); }; \
 \
private: \
void createLabel(string show) { \
	_label = Label::create(show, QE_Font, 24); \
	_label->setAnchorPoint(Vec2(0, 0)); \
	addChild(_label); \
}; \
virtual void editBoxReturn(EditBox* editBox) {}; \
EditBox* createEditBox(string normalPngFile) { \
	EditBox* box = EditBox::create(Size(220, 38), Scale9Sprite::create(normalPngFile), Scale9Sprite::create("wite_edit.png")); \
	box->setFontName(QE_Font); \
	box->setFontSize(25); \
	box->setFontColor(Color3B(0, 0, 255)); \
	box->setPlaceholderFontName(QE_Font); \
	box->setPlaceholderFontSize(25); \
	box->setPlaceholderFontColor(Color3B(255, 0, 0)); \
	box->setMaxLength(16);   /*设置文本框中文本的最大长度*/ \
	box->setInputMode(EditBox::InputMode::SINGLE_LINE); /*输入键盘模式,任何符号*/ \
	box->setReturnType(EditBox::KeyboardReturnType::DONE);/*设置软键盘中回车按钮的样子*/ \
	box->setDelegate(this); /*开启委托，文本框代理，需要实现EditBoxDelegate代理中的方法，就可以对EditBox进行控制*/ \
	addChild(box); \
	return box; \
}