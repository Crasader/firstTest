#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "EnumCommon.h"
#include "LoadScene.h"
#include "EnumEvent.h"

using namespace cocos2d::extension;
USING_NS_CC;

enum LoadType{LArmature = 0, LSprite};

class LoadManager : public CCNode
{
public:
	LoadManager(void);
	~LoadManager(void);

	static LoadManager* shardLoadManager();
	bool init();
	void timeCheck(float dt);

	void load(SCENE target);
	void addLoadItem(const char *plist, const char *png, const char *json);
	void addLoadItem(const char *plist, const char *png);

protected:
	float mAll;
	int mLoaded;
	CCArray* mLoadArray;

	SCENE mNextScene;
	CCScene* mLoadScene;

	void doProgressCall(float pro);
	void changeScene();
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