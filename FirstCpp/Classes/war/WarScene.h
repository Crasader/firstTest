#pragma once

#include "cocos2d.h"
#include "PartenerView.h"
#include "BaseLayer.h"

USING_NS_CC;

const int posArr1[9] = {0,1,2,3,4,5,6,7,8};
const int posArr2[9] = {3,4,5,0,1,2,6,7,8};
const int posArr3[9] = {6,7,8,3,4,5,0,1,2};

class WarScene : public BaseLayer
{
private:

	CCNode* mLayerBg; // ������
	CCNode* mLayerEntity; // ʵ���
	CCNode* mLayerEffect; // Ч����
	CCNode* mLayerUI; // UI��

	float mTouchX; // ����ʱx
	float mBeforX; // �ƶ�ǰx

	PartenerView* stone; // �����ã��̶�Ŀ�꣬����

	// function
	PersonView* getTargetBySelfPos(int selfType, int selfPos);

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

