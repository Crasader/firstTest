#pragma once

#include "cocos2d.h"
#include "PartenerView.h"

USING_NS_CC;

//LRESULT myWndProcHook(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed);

class WarScene : public cocos2d::CCLayer
{
private:
	PartenerView* stone; // 测试用，固定目标，靶子

public:
	WarScene(void);
	~WarScene(void);

	virtual bool init();
	static cocos2d::CCScene* scene();
	virtual void update(float delta);

	CCSprite* bg1; // 背景1
	CCSprite* bg2; // 背景2
	CCSprite* bg;

	// function
	void onTimerHandler(float dt); // 秒计时器处理函数
	void checkDeep(); // 检查深度排序
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); // 触摸开始
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); // 触摸移动
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); // 触摸结束

	// varriable
	PartenerView* hero;

	

	CREATE_FUNC(WarScene);
};

