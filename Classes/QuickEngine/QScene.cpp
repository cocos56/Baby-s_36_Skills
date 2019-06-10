#pragma execution_character_set("utf-8")

#include "QScene.h"

void QScene::saveNowSceneToFile()
{
	QE_get_winSize;
	TextureCache::getInstance()->removeUnusedTextures();
	//相当于截取暂停这一刹那的游戏界面图，并把它保存成pause.png
	auto texture = RenderTexture::create(winSize.width, winSize.height);
	texture->begin();
	Director::getInstance()->getRunningScene()->visit();
	texture->end();
	texture->saveToFile("pause.png", Image::Format::PNG);
}