#include "LoadManager.h"
#include "war/WarScene.h"

// singleton
static LoadManager* mLoadManager = NULL;

/////////////////
// LoadInfoVo
/////////////////
bool LoadInfoVo::init()
{
	return true;
}



/////////////////
// LoadManager
/////////////////
LoadManager::LoadManager(void)
{

}

LoadManager::~LoadManager(void)
{
	CC_SAFE_DELETE(mLoadManager);
	CC_SAFE_RELEASE_NULL(mLoadArray);
}

LoadManager* LoadManager::shardLoadManager()
{
	if (mLoadManager == NULL)
	{
		mLoadManager = new LoadManager();
		mLoadManager->init();
	}
	return mLoadManager;
}

bool LoadManager::init()
{
	mLoadScene = NULL;
	mNextScene = SCENE_MAIN;
	mLoaded = 0;
	mAll = 0;
	mLoadArray = CCArray::create();
	mLoadArray->retain();
	return true;
}

void LoadManager::addLoadItem(const char *imagePath, const char *plistPath, const char *jsonPath)
{
	mAll++;
	LoadInfoVo* temp = LoadInfoVo::create();
	temp->mType = LArmature;
	temp->mImagePath = imagePath;
	temp->mPlistPath = plistPath;
	temp->mJsonPath = jsonPath;
	mLoadArray->addObject(temp);
	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath, plistPath, jsonPath);
}

void LoadManager::addLoadItem(const char *imagePath, const char *plistPath)
{
	mAll++;
	LoadInfoVo* temp = LoadInfoVo::create();
	temp->mType = LSprite;
	temp->mImagePath = imagePath;
	temp->mPlistPath = plistPath;
	mLoadArray->addObject(temp);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(imagePath, plistPath);
}

void LoadManager::load(SCENE target)
{
	mNextScene = target;

	mLoadScene = LoadScene::scene();
	CCDirector::sharedDirector()->replaceScene(mLoadScene);
	mLoadScene->addChild(this);

	for (int i = mLoadArray->count() - 1; i >= 0; i--) 
	{
		LoadInfoVo* pObj = (LoadInfoVo*)mLoadArray->objectAtIndex(i);
		
		switch (pObj->mType)
		{
		case LArmature:
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(pObj->mImagePath.c_str(), pObj->mPlistPath.c_str(), pObj->mJsonPath.c_str());
			//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("fuwang/FuWang0.png", "fuwang/FuWang0.plist", "fuwang/FuWang.ExportJson");
			break;
		case LSprite:
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pObj->mImagePath.c_str(), pObj->mPlistPath.c_str());
			break;
		}
		mLoadArray->removeObject(pObj);
		mLoaded++;
		doProgressCall(mLoaded / mAll);
	}

	// 全部加载完毕
	mAll = 0;
	mLoaded = 0;
	changeScene();
}

void LoadManager::doProgressCall(float pro)
{
	CCLog("load progress：%d", (int)(pro * 100));
}

void LoadManager::changeScene()
{
	switch (mNextScene)
	{
	case SCENE_MAIN:

		break;
	case SCENE_WAR:
		CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_SCENE_VIEW_WAR, NULL);
		break;
	}

}