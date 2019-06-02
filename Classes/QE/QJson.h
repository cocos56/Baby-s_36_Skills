#pragma once

/*
Quick Engine所属快速Json读写模块
含：
1.QJson类
用途：用于快速读写Json文件
*/

#include "json/document.h"
#include "json/reader.h"
//#include "json/writer.h"
#include  "json/stringbuffer.h"
typedef rapidjson::Value JValue;
typedef rapidjson::Document JDoc;

#include "QE.h"

class QJson
{
	QE_SINGLETON_H(QJson);
public:
	static JDoc getDocFromJsonFile();

	//get the array of key from value
	static JValue& getArray(string key, JValue& value);
	static int getInt(string key, JValue& value);
	static string getString(string key, JValue& value);
};