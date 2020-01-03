#pragma execution_character_set("utf-8")
#pragma once

#include "QuickEngine.h"

/*
Quick Engine所属快速动画模块
含：
1.QAnimate类
用途：用于快速创建动画
*/

class QAnimate
{
public:
	static void createFramsPlayerFromPlistFile(const string& fileName, vector<Sprite*> &sprites, int x, int y, Layer* layer, string dirName = "", float scale = 1.0f);
	//从所有动画帧中播放某一帧，num是需要播放的帧序号，默认情况下num为1，如果传进来的num<=0，则会隐藏所有帧，即停止动画播放，如果传进来的num>=frames.size()，则会显示最后一帧
	static void playFramFromFrams(vector<Sprite*> &frames, int num = 1);
	static void initAnimateFromPlistFile(Animate*& animate, Sprite*& sprite, int x, int y, const string& fileName, string dirName = "", float scale = 1.0f, bool isRestoreOriginalFrame =true);
private:
	//通过plist文件解析出来当前的动画有多少个动画帧，通过plist文件只是解析出来一个数字，这个数字是当前动画的帧数，把这个帧数保存在本类的静态成员num中
	static void initFramsNumFromPlistFile(const string& fileName);
	static int num;
};