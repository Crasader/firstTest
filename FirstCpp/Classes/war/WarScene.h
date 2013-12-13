//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 战场场景
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 战斗主要逻辑
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "cocos2d.h"
#include "BaseLayer.h"
#include "PersonView.h"

USING_NS_CC;

const int posArr1[9] = {0,1,2,3,4,5,6,7,8};
const int posArr2[9] = {3,4,5,0,1,2,6,7,8};
const int posArr3[9] = {6,7,8,3,4,5,0,1,2};

class WarScene : public BaseLayer
{
public:
	WarScene(void);
	virtual ~WarScene(void);
public:
	static cocos2d::CCScene* scene();
	virtual void onEnter();
	virtual void onExit();
	virtual bool init();
	virtual void update(float delta);
public:
	void purgeSelf(); // 
	void menuCloseCallback(CCObject* pSender);
	void onTimerHandler(float dt); // 秒计时器处理函数
	void onSkillTimerHandler(float dt); // 技能计时器函数
	void checkDeep(); // 检查深度排序
public:
	// 重写触摸函数
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); // 触摸开始
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); // 触摸移动
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); // 触摸结束
public:
	void addEntity(CCNode* entity);
	void addEffect(CCObject* effect);
	void addTouchedEntity(CCObject* p);
	void entityTouchEnd(CCObject* obj);
	void onEntityDie(CCObject* value);
	//void onUseSkill(CCObject* value);
	void onSelectHeadbtn(CCObject* value);

	void initUI(); // 初始化ui层

	// varriable
	//PartenerView* hero;

	CREATE_FUNC(WarScene);


private:
	CCNode* mLayerBg; // 背景层
	CCNode* mLayerEntity; // 实体层
	CCNode* mLayerEffect; // 效果层
	CCNode* mLayerUI; // UI层

	UILayer* mBgUILayer;

	float mTouchX; // 触摸时x
	float mBeforX; // 移动前x

	UIWidget* mSkillBar; // 技能组件集合

	CCArray* touchEntityArr;
	PersonView* mTouchEntity;

	CCArray* mSkillBtnArr; // 技能按钮数组
	CCArray* mHeadBtnArr; // 头像数组

	//PartenerView* stone; // 测试用，固定目标，靶子

	// function
	PersonView* getTargetBySelfPos(int selfType, int selfPos);
};

