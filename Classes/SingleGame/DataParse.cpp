#pragma execution_character_set("utf-8")

#include "DataParse.h"

void DataParse::CopyFile()
{
	std::string writeablePath = FileUtils::getInstance()->getWritablePath();
	writeablePath = writeablePath + "Data.json";
	
	std::string filePath = FileUtils::getInstance()->fullPathForFilename("Data.json");
	if (!FileUtils::getInstance()->isFileExist(writeablePath))
	{
		std::string data = FileUtils::getInstance()->getStringFromFile(filePath);
		FILE* file = fopen(writeablePath.c_str(), "w");
		if (file)
		{
			fputs(data.c_str(), file);
			fclose(file);
		}
	}
	
}

int  DataParse::getclok(int levelIndex)
{
	std::string writeablePath = FileUtils::getInstance()->getWritablePath();
	//获取完整路径
	writeablePath = writeablePath + "Data.json";
	//将一个文件内容读取为字符串
	std::string data = FileUtils::getInstance()->getStringFromFile(writeablePath);
	//解析对象 
	rapidjson::Document doc;
	//开始解析
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	//判断解析是否出现问题
	if (doc.HasParseError())
	{
		return 0;
	}

	char levelName[20];
	sprintf(levelName, "level_%d", levelIndex);
	int num = doc[levelName]["lock"].GetInt();
	return num;
}

__Dictionary* DataParse::getChapter(int chapterIndex)
{
	CopyFile();
	//获取可读写路径
	std::string writeablePath = FileUtils::getInstance()->getWritablePath();
	//获取完整路径
	writeablePath = writeablePath + "Data.json";
	
	
	//获取资源
	
	std::string data = FileUtils::getInstance()->getStringFromFile(writeablePath);
	//解析
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	
	if (doc.HasParseError())
	{
		
		return 0;
	}
	//存入字典
	
	__Dictionary* dic = __Dictionary::create();
	
	//初始化
	
	char level[20];
	sprintf(level, "level_%d", chapterIndex);
	/*for (int i = 1; i <= 7; i++)
	{*/
		//定义键
		char lock[20];
		sprintf(lock, "level_%d_lock", chapterIndex);
		char LogoScene[20];
		sprintf(LogoScene, "level_%d_star",chapterIndex);
		//从doc中获取值
		
		//因为值是int型的需要转变为对象
		String* lockValue = String::create(doc[level]["lock"].GetString());
		String* starValue = String::create(doc[level]["LogoScene"].GetString());
		log("asdfashfh");
		dic->setObject(lockValue, lock);
		dic->setObject(starValue, LogoScene);
	//}
	return dic;   
}

int DataParse::getNum( int levelIndex)
{
	//recouse
	std::string writeablePath = FileUtils::getInstance()->getWritablePath();
	writeablePath = writeablePath + "Data.json";
	std::string data = FileUtils::getInstance()->getStringFromFile(writeablePath);
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	if (doc.HasParseError())
	{
		return 0;
	}
	char levelName[20];
	sprintf(levelName, "level_%d", levelIndex);
	int num = doc[levelName]["num"].GetInt();
	return num;
}

int DataParse::getStar( int levelIndex)
{
	std::string writeablePath = FileUtils::getInstance()->getWritablePath();
	writeablePath = writeablePath + "Data.json";
	std::string data = FileUtils::getInstance()->getStringFromFile(writeablePath);
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	if (doc.HasParseError())
	{
		return 0;
	}
	char levelName[20];
	sprintf(levelName, "level_%d", levelIndex);
	int num = doc[levelName]["LogoScene"].GetInt();
	return num;
}

void DataParse::setStar( int levelIndex, int starNum)
{
	std::string writeablePath = FileUtils::getInstance()->getWritablePath();
	writeablePath = writeablePath + "Data.json";
	std::string data = FileUtils::getInstance()->getStringFromFile(writeablePath);
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	if (doc.HasParseError())
	{
		return;
	}
	char levelName[20];
	sprintf(levelName, "level_%d", levelIndex);
	int starNum_Data = doc[levelName]["LogoScene"].GetInt();
	if (starNum_Data<=starNum)
	{
		doc[levelName]["LogoScene"].SetInt(starNum);
		if (starNum == 3 && levelIndex != 7)
		{
			char nextLevelName[20];
			sprintf(nextLevelName, "level_%d", levelIndex + 1);
			doc[nextLevelName]["lock"].SetInt(0);
		}
		writefile(doc, writeablePath);
	}
}

void DataParse::writefile(rapidjson::Document& document, std::string path)
{
	rapidjson::StringBuffer buffer;//初始化缓存
	//初始化写入器
	rapidjson::Writer<rapidjson::StringBuffer>writer(buffer);
	document.Accept(writer);//json 写入buffer
	//将原来的文件内容覆盖掉
	FILE *file = fopen(path.c_str(), "w");
	if (file)
	{
		fputs(buffer.GetString(), file);//覆盖
		fclose(file);
	}
}