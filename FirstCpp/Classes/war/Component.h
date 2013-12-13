#pragma once

#include "cocos2d.h"

USING_NS_CC;

// 血条
class BloodBar : public cocos2d::CCNode
{
public:
	BloodBar();
	virtual ~BloodBar();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(BloodBar);
	virtual bool init();
	virtual void setPercentage(float pro);

protected:
	CCProgressTimer* mProgressBar;
};


//技能按钮
class SkillBtn : public CCNode, public cocos2d::CCTargetedTouchDelegate
{
public:
	SkillBtn();
	virtual ~SkillBtn();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(SkillBtn);
	virtual bool init();
	void setId(int value);
	void setPercent(float value);

	//重写CCTouchDelegate方法
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); // 触摸开始
	//virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); // 触摸移动
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); // 触摸结束

private:
	CCSprite* mBgImg;
	CCSprite* mGrayImg;
	CCProgressTimer* mPro;
	int mId;
};

//飘血字
class BloodFont : public CCNode
{
public:
	BloodFont();
	virtual ~BloodFont();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(BloodFont);
	virtual bool init();
	void initBloodFont(int value,float posx, float posy);
private:
	void moveComplete();
	CCLabelAtlas* labelAtlas;
};

//头像
class HeadBtn : public CCNode, public cocos2d::CCTargetedTouchDelegate
{
public:
	HeadBtn();
	virtual ~HeadBtn();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(HeadBtn);
	virtual bool init();

	void setSelected(bool flag); // 设置选中状态
	bool isSelected();

	void setTaget(CCNode* target);
	void checkSkillTime(); // 检测技能冷却时间
	void useSkill(CCObject* value);
	void setPercentage(float pro);

	//重写CCTouchDelegate方法
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); // 触摸开始
	//virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); // 触摸移动
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); // 触摸结束

private:
	bool mIsSelect;
	CCSprite* mHeadIcon;
	SkillBtn* mSkillBtn;
	CCNode* mTarget;
	BloodBar* mBloodBar;
};

//说话气泡