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
LoadManager::LoadManager(void):mAllNum(0), mLoaded(0),mArmatureNum(0),mArmatureLoaded(0)
{

}

LoadManager::~LoadManager(void)
{
	CC_SAFE_RELEASE_NULL(mLoadArray);
	CC_SAFE_RELEASE_NULL(mSpriteLoadArray);
	CC_SAFE_RELEASE_NULL(mArmatureLoadArray);
}

void LoadManager::pure()
{
	if (mLoadManager)
	{
		delete mLoadManager;
		mLoadManager = NULL;
	}
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
	mLoadArray = CCArray::create();
	CC_SAFE_RETAIN(mLoadArray);
	mSpriteLoadArray = CCArray::create();
	CC_SAFE_RETAIN(mSpriteLoadArray);
	mArmatureLoadArray = CCArray::create();
	CC_SAFE_RETAIN(mArmatureLoadArray);
	return true;
}

void LoadManager::addLoadItem(const char *imagePath, const char *plistPath, const char *jsonPath)
{
	mArmatureNum++;
	LoadInfoVo* temp = LoadInfoVo::create();
	temp->mType = LArmature;
	temp->mImagePath = imagePath;
	temp->mPlistPath = plistPath;
	temp->mJsonPath = jsonPath;
	mArmatureLoadArray->addObject(temp);
	//CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(imagePath, plistPath, jsonPath);
}

void LoadManager::addLoadItem(const char *imagePath, const char *plistPath)
{
	mAllNum++;
	LoadInfoVo* temp = LoadInfoVo::create();
	temp->mType = LSprite;
	temp->mImagePath = imagePath;
	temp->mPlistPath = plistPath;
	mLoadArray->addObject(temp);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(imagePath, plistPath);
}

void LoadManager::addLoadItem(const char *imagePath)
{
	mAllNum++;
	LoadInfoVo* temp = LoadInfoVo::create();
	temp->mType = LImage;
	temp->mImagePath = imagePath;
	mLoadArray->addObject(temp);
}

void LoadManager::load(SCENE target)
{
	mNextScene = target;

	if (mAllNum + mArmatureNum <= 0)
	{
		changeScene();
		return;
	}

	CCScene* tempSc = LoadScene::scene();
	mLoadScene = (LoadScene*)(tempSc->getChildren()->objectAtIndex(0));
	CCDirector::sharedDirector()->replaceScene(tempSc);

	if (mLoadArray->count() == 0)
	{
		loadArmature();
		return;
	}

	for (int i = mLoadArray->count() - 1; i >= 0; i--) 
	{
		LoadInfoVo* pObj = (LoadInfoVo*)mLoadArray->objectAtIndex(i);
		
		switch (pObj->mType)
		{
		//case LArmature:
		//	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(pObj->mImagePath.c_str(), 
		//		pObj->mPlistPath.c_str(), 
		//		pObj->mJsonPath.c_str(),
		//		this,
		//		schedule_selector(LoadManager::loadedArmatureCall));
		//	break;
		case LSprite:
			mSpriteLoadArray->addObject(pObj);
			CCTextureCache::sharedTextureCache()->addImageAsync(pObj->mImagePath.c_str(),
				this,
				callfuncO_selector(LoadManager::loadedImageCall));
			break;
		case LImage:
			CCTextureCache::sharedTextureCache()->addImageAsync(pObj->mImagePath.c_str(),
				this,
				callfuncO_selector(LoadManager::loadedImageCall));
			break;
		}
		mLoadArray->removeObject(pObj);
	}
}

void LoadManager::loadedArmatureCall(float f)
{
	mArmatureLoaded++;
	doProgressCall();
	if (mLoaded + mArmatureLoaded >= mAllNum + mArmatureNum)
	{
		changeScene();
	}
}

void LoadManager::loadedImageCall(CCObject* obj)
{
	mLoaded++;
	doProgressCall();
	if (mLoaded >= mAllNum)
	{
		loadArmature();
	}
}

void LoadManager::loadArmature()
{
	if (mArmatureNum <= 0)
	{
		changeScene();
		return;
	}

	for (int i = mArmatureLoadArray->count() - 1; i >= 0; i--) 
	{
		LoadInfoVo* pObj = (LoadInfoVo*)mArmatureLoadArray->objectAtIndex(i);
		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(pObj->mImagePath.c_str(), 
			pObj->mPlistPath.c_str(), 
			pObj->mJsonPath.c_str(),
			this,
			schedule_selector(LoadManager::loadedArmatureCall));
		mArmatureLoadArray->removeObject(pObj);
	}
}

void LoadManager::doProgressCall()
{
	if (mAllNum + mArmatureNum > 0)
	{
		float pro = (float)(mLoaded + mArmatureLoaded) / (mAllNum + mArmatureNum);
		mLoadScene->setProgress(pro);
		if (pro >= 1)
		{
			for (int i = mSpriteLoadArray->count() - 1; i >= 0; i--)
			{
				LoadInfoVo* pObj = (LoadInfoVo*)mSpriteLoadArray->objectAtIndex(i);
				CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(pObj->mPlistPath.c_str());
			}
			mSpriteLoadArray->removeAllObjects();
		}
	}
}

void LoadManager::changeScene()
{
	mAllNum = 0;
	mLoaded = 0;
	mArmatureNum = 0;
	mArmatureLoaded = 0;
	switch (mNextScene)
	{
	case SCENE_MAIN:

		break;
	case SCENE_WAR:
		CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_SCENE_VIEW_WAR, NULL);
		break;
	}
}