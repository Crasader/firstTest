#include "LoadScene.h"

CCScene* LoadScene::scene()
{
	CCScene* mScene = CCScene::create();
	LoadScene* mLoadScene = LoadScene::create();

	mScene->addChild(mLoadScene);

	return mScene;
}

bool LoadScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	return true;
}