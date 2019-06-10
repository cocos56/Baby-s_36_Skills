#pragma execution_character_set("utf-8")

#include "QJson.h"

JDoc QJson::doc, QJson::tempDoc;

void QJson::initDocFromJsonFile(string fileName)
{
	//获取Json文件所在的路径
	string  filefullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
	//CCLOG("fullPath=%s", filefullPath.c_str());//测试filefullPath的全路径（如D:/projects/SnailGoHome/Resources/Data.json）
	Data data = FileUtils::getInstance()->getDataFromFile(filefullPath);
	//用Data构建content
	string content = string((const char*)data.getBytes(), 0, data.getSize());

	//用content构建document
	initDocWithString(content);
}

void QJson::initDocWithString(string content)
{
	doc.Parse<0>(content.c_str());
	//解析错误
	CCASSERT(!doc.HasParseError(), "Parsing to document failed.");
	//CCLOG("Parsed to document successfully !");
}

JValue& QJson::getArray(string key, JValue& value)
{
	//确认拥有相应的值
	CC_ASSERT(value.HasMember(key.c_str()));

	//确认所捕获的值是Array类型的
	CC_ASSERT(value[key.c_str()].IsArray());
	return value[key.c_str()];
}

int QJson::getInt(string key, JValue& value)
{
	//确认拥有相应的值
	CC_ASSERT(value.HasMember(key.c_str()));
	//确认所捕获的值是Int类型的
	CC_ASSERT(value[key.c_str()].IsInt());
	return value[key.c_str()].GetInt();
}

string QJson::getString(string key, JValue& value)
{
	//确认拥有相应的值
	CC_ASSERT(value.HasMember(key.c_str()));
	//确认所捕获的值是String类型的
	CC_ASSERT(value[key.c_str()].IsString());
	//返回最终需要的值
	return value[key.c_str()].GetString();
}

string QJson::getString(string key)
{
	// 确认拥有相应的值
	CC_ASSERT(doc.HasMember(key.c_str()));
	//确认所捕获的值是String类型的
	CC_ASSERT(doc[key.c_str()].IsString());
	//返回最终需要的值
	return doc[key.c_str()].GetString();
}

string QJson::getString()
{
	StringBuffer buffer;
	Writer<StringBuffer>writer(buffer);
	doc.Accept(writer);
	return buffer.GetString();
}