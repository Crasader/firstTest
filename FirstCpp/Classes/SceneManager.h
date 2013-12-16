//-----------------------------------------------------------------------------------------------------------------------------
// ����: ����������
// ����: lvxiangsong
// ����: 2013-10-8
// ����: ����������
// �汾: 
//
// �޸���           ����	           ����		
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
	void viewToMain(CCObject* obj); // ����������
	void viewToWar(CCObject* obj); // ����ս������
};