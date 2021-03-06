﻿#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine/QuickEngine.h"

class NetworkBaseScene
{
public:
	//服务器返回信息相关
	//virtual void dealServerResponse(int statusCode) {};

protected:
	static Label* _logLabel;

	//标签相关
	void initLabel() {};

	//菜单相关
	void initMenu() {};

	static Label* _label;
	static EditBox* _box;
};

#define NW_InitLogLabel(__x__, __y__) _logLabel = createLabel(Connect::getStatus(int(Connect::_nowEvent)*100 + 11)); \
_logLabel->setPosition(__x__, __y__);

#define NW_BaseScene public: \
static void dealServerResponse(string str) {_logLabel->setString(str);}; \
 \
private: \
	Label* createLabel(string show) \
	{ \
		_label = Label::create(show, QE_Font, 24); \
		_label->setAnchorPoint(Vec2(0, 0)); \
		_label->setColor(Color3B::BLACK); \
		addChild(_label); \
		return _label; \
	}; \
	 \
	virtual void editBoxReturn(EditBox* editBox) {}; \
	 \
	EditBox* createEditBox(string normalPngFile, string pressedPngFile) \
	{ \
		_box = EditBox::create(Size(220, 38),  Scale9Sprite::create(normalPngFile), Scale9Sprite::create(pressedPngFile)); \
		_box->setFontName(QE_Font); \
		_box->setFontSize(25); \
		_box->setFontColor(Color3B(0, 0, 255)); \
		_box->setPlaceholderFontName(QE_Font); \
		_box->setPlaceholderFontSize(25); \
		_box->setPlaceholderFontColor(Color3B(255, 0, 0)); \
		_box->setMaxLength(16);   /*设置文本框中文本的最大长度*/ \
		_box->setInputMode(EditBox::InputMode::SINGLE_LINE); /*输入键盘模式,除换行外的所有符号*/ \
		_box->setReturnType(EditBox::KeyboardReturnType::DONE);/*设置软键盘中回车按钮的样子*/ \
		_box->setAnchorPoint(Vec2(0, 0)); \
		_box->setDelegate(this); /*开启委托，文本框代理，需要实现EditBoxDelegate代理中的方法，就可以对EditBox进行控制*/ \
		addChild(_box); \
		return _box; \
	} \
 \
	EditBox* createEditBox(string file) { return createEditBox(file, file); } \
	 \
	EditBox* createEditBox(string file, string text, int maxLength) \
	{ \
		_box = createEditBox(file); \
		_box->setText(text.c_str()); \
		_box->setPlaceHolder(text.c_str()); /*当编辑框中没有任何字符（或输入字符前）的提示文本,即占位符*/ \
		_box->setMaxLength(maxLength);   /*设置文本框中文本的最大长度*/ \
		return _box; \
	}

#include "QE.h"