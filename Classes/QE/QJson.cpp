#include "QJson.h"

QE_SINGLETON_CPP(QJson);

JDoc QJson::getDocFromJsonFile()
{
	//获取Json文件所在的路径
	string  filefullPath = FileUtils::getInstance()->fullPathForFilename("Data.json");
	CCLOG("fullPath=%s", filefullPath.c_str());//测试filefullPath的全路径（如D:/projects/SnailGoHome/Resources/Data.json）
	Data data = FileUtils::getInstance()->getDataFromFile(filefullPath);
	//用Data构建content
	string content = string((const char*)data.getBytes(), 0, data.getSize());

	//用content构建document
	JDoc document;
	document.Parse<0>(content.c_str());

	//解析错误
	CCASSERT(!document.HasParseError(), "Parsing to document failure.");
	CCLOG("Parsed to document successfully !");

	//判断是否是对象
	CC_ASSERT(document.IsObject());

	return document;
}

JValue& QJson::getArray(string key, JValue& value)
{
	//确认拥有相应的值
	CC_ASSERT(value.HasMember(key.c_str()));
	JValue& v1 = value[key.c_str()];

	//确认所捕获的值是Array类型的
	CC_ASSERT(v1.IsArray());
	return v1;
}

int QJson::getInt(string key, JValue& value)
{
	//确认拥有相应的值
	CC_ASSERT(value.HasMember(key.c_str()));
	JValue& v1 = value[key.c_str()];

	//确认所捕获的值是Int类型的
	CC_ASSERT(v1.IsInt());
	int v2 = v1.GetInt();

	//释放临时变量所占用的空间
	v1.~GenericValue();
	
	//返回最终需要的值
	return v2;
}

string QJson::getString(string key, JValue& value)
{
	//确认拥有相应的值
	CC_ASSERT(value.HasMember(key.c_str()));
	JValue& v1 = value[key.c_str()];

	//确认所捕获的值是String类型的
	CC_ASSERT(v1.IsString());
	string v2 = v1.GetString();

	//释放临时变量所占用的空间
	v1.~GenericValue();

	//返回最终需要的值
	return v2;
}