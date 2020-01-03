#pragma execution_character_set("utf-8")
#pragma once

#include "QE.h"

class DataParse
{
public:
	static Dictionary* getChapter(int chapterIndex);
	static void CopyFile();

	static int getNum( int levelIndex);
	static int getStar( int levelIndex);
	static void setStar( int levelIndex, int starNum);
	static void writefile(rapidjson::Document& document, std::string path);
	static int getclok(int levelIndex);
};
