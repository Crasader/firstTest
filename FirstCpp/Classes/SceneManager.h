//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 场景管理器
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 场景管理器
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "EnumEvent.h"
#include "war/WarScene.h"
#include "GameScene.h"

using namespace cocos2d::extension;
USING_NS_CC;

class SceneManager : public CCNode
{
public:
	SceneManager(void);
	virtual ~SceneManager(void);

	static SceneManager* shardSceneManager();
	bool init();
	static void pure();

private:
	void viewToMain(CCObject* obj); // 进入主场景
	void viewToWar(CCObject* obj); // 进入战斗场景
};