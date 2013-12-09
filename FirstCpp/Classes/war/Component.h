#pragma once

#include "cocos2d.h"

USING_NS_CC;

// Ѫ��
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


//���ܰ�ť
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

	//��дCCTouchDelegate����
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); // ������ʼ
	//virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); // �����ƶ�
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); // ��������

private:
	CCSprite* mBgImg;
	CCSprite* mGrayImg;
	CCProgressTimer* mPro;
	int mId;
};

//ƮѪ��
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

//ͷ��
class HeadBtn : public CCNode, public cocos2d::CCTargetedTouchDelegate
{
public:
	HeadBtn();
	virtual ~HeadBtn();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(HeadBtn);
	virtual bool init();

	////��дCCTouchDelegate����
	//virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); // ������ʼ
	////virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); // �����ƶ�
	//virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); // ��������
private:
};

//˵������