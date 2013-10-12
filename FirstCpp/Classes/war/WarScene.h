#pragma once

#include "cocos2d.h"
#include "PartenerView.h"

USING_NS_CC;

//LRESULT myWndProcHook(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed);

class WarScene : public cocos2d::CCLayer
{
private:
	PartenerView* stone; // �����ã��̶�Ŀ�꣬����

public:
	WarScene(void);
	~WarScene(void);

	virtual bool init();
	static cocos2d::CCScene* scene();
	virtual void update(float delta);

	CCSprite* bg1; // ����1
	CCSprite* bg2; // ����2
	CCSprite* bg;

	// function
	void onTimerHandler(float dt); // ���ʱ��������
	void checkDeep(); // ����������
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); // ������ʼ
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); // �����ƶ�
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); // ��������

	// varriable
	PartenerView* hero;

	

	CREATE_FUNC(WarScene);
};

