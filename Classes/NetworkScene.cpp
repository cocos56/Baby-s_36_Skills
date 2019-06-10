#pragma execution_character_set("utf-8")

#include "QE.h"

Label* NetworkScene::_label, * NetworkScene::_logLabel;

void NetworkScene::dealServerResponse() { dealServerResponse(QJson::getString("消息")); };
void NetworkScene::dealServerResponse(string str) { _logLabel->setString(str); };

void NetworkScene::createLabel(string show)
{
	_label = Label::create(show, QE_Font, 24);
	_label->setAnchorPoint(Vec2(0, 0));
}

EditBox* NetworkScene::createEditBox(string normalPngFile, EditBoxDelegate* delegate)
{
	EditBox* box = EditBox::create(Size(220, 38), Scale9Sprite::create(normalPngFile), Scale9Sprite::create("wite_edit.png"));
	box->setFontName(QE_Font);
	box->setFontSize(25);
	box->setFontColor(Color3B(0, 0, 255));
	box->setPlaceholderFontName(QE_Font);
	box->setPlaceholderFontSize(25);
	box->setPlaceholderFontColor(Color3B(255, 0, 0));
	box->setMaxLength(16);   //设置文本框中文本的最大长度
	box->setInputMode(EditBox::InputMode::SINGLE_LINE);//输入键盘模式,任何符号
	box->setReturnType(EditBox::KeyboardReturnType::DONE);//设置软键盘中回车按钮的样子
	box->setDelegate(delegate);
	return box;
}