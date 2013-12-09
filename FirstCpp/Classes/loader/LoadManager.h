#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "EnumCommon.h"
#include "LoadScene.h"
#include "EnumEvent.h"

using namespace cocos2d::extension;
USING_NS_CC;

enum LoadType{
	LArmature = 0, 
	LSprite,
	LImage
};

class LoadManager : public CCNode
{
public:
	LoadManager(void);
	~LoadManager(void);

	static LoadManager* shardLoadManager();
	bool init();
	static void pure();

	void load(SCENE target);
	void addLoadItem(const char *plist, const char *png, const char *json);
	void addLoadItem(const char *plist, const char *png);
	void addLoadItem(const char *png);

protected:
	int mAllNum;
	int mLoaded;
	int mArmatureNum;
	int mArmatureLoaded;
	
	CCArray* mLoadArray;
	CCArray* mArmatureLoadArray;
	CCArray* mSpriteLoadArray;

	SCENE mNextScene;
	LoadScene* mLoadScene;

	void loadedImageCall(CCObject* obj);
	void loadedArmatureCall(float pro);
	void doProgressCall();
	void changeScene();
	void loadArmature();
};

class LoadInfoVo : public CCObject
{
public:
	std::string mImagePath;
	std::string mPlistPath;
	std::string mJsonPath;
	LoadType mType;

	CREATE_FUNC(LoadInfoVo);
	bool init();
};