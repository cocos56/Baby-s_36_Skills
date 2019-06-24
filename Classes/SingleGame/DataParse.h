
#include"cocos2d.h"
#include"json/rapidjson.h"
#include"json/document.h"
using namespace cocos2d;

class DataParse
{
public:
	static __Dictionary* getChapter(int chapterIndex);
	static void CopyFile();

	static int getNum( int levelIndex);
	static int getStar( int levelIndex);
	static void setStar( int levelIndex, int starNum);
	static void writefile(rapidjson::Document& document, std::string path);
	static int getclok(int levelIndex);

	
};
