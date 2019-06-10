#pragma execution_character_set("utf-8")
#pragma once

/*
Quick Engine所属快速Json读写模块
含：
1.QJson类
用途：用于快速读写Json数据
*/

#include "json/document.h"
#include "json/rapidjson.h"
#include "json/reader.h"
#include "json/writer.h"
#include  "json/stringbuffer.h"

using namespace rapidjson;
typedef rapidjson::Value JValue;
typedef JValue::StringRefType JString;
typedef Document JDoc;

#define QE_ToJStr(text) rapidjson::StringRef(text)
#define QE_strToJStr(text) QE_ToJStr(text.c_str())

#include "QE.h"

class QJson
{
public:
	static JDoc doc;
	static JDoc tempDoc;

	static void initDocFromJsonFile(string fileName = "Data.json");
	static void initDocWithString(string content);

	//get the array of key from value
	static JValue& getArray(string key, JValue& value);
	static int getInt(string key, JValue& value);
	static string getString(string key, JValue& value);
	static string getString(string key);
	static string getString();
	static void addMember(JString name, JString value) { doc.AddMember(name, value, doc.GetAllocator()); };
	static void emptyDoc(){ doc.Parse<0>("{}"); }
};

/*
rapidjson::Value value，只是一个定义，还没有决定其数据类型，如果明确value的类型，再转成相应的格式

Value的类型包括：int, double, string, bool, array, object, null

RapidJson除了能够读取和修改数据，还能添加和删除数据
添加数据时，先获取一个分配器
rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
添加一个数：
doc.AddMember("age", 15 , allocator);
添加一个null对象
rapidjson::Value nullObject(rapidjson::kNullType);
doc.AddMember("null", nullObject, allocator);
添加一个对象
rapidjson::Value obj(rapidjson::kObjectType);
obj.AddMember("name", "xiaoli", allocator);
obj.AddMember("age", 20, allocator);
obj.AddMember("height", 180, allocator);
doc.AddMember("personInfo", obj, allocator);
添加一个数组
rapidjson::Value arr(rapidjson::kArrayType);
arr.PushBack(1, allocator);
arr.PushBack("string in array", allocator);
arr.PushBack(obj, allocator);
doc.AddMember("arr", arr, allocator);
*/