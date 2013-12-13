//-----------------------------------------------------------------------------------------------------------------------------
// ����: ս������
// ����: lvxiangsong
// ����: 2013-10-8
// ����: ս����Ҫ�߼�
// �汾: 
//
// �޸���           ����	           ����		
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
	void onTimerHandler(float dt); // ���ʱ��������
	void onSkillTimerHandler(float dt); // ���ܼ�ʱ������
	void checkDeep(); // ����������
public:
	// ��д��������
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); // ������ʼ
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); // �����ƶ�
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); // ��������
public:
	void addEntity(CCNode* entity);
	void addEffect(CCObject* effect);
	void addTouchedEntity(CCObject* p);
	void entityTouchEnd(CCObject* obj);
	void onEntityDie(CCObject* value);
	//void onUseSkill(CCObject* value);
	void onSelectHeadbtn(CCObject* value);

	void initUI(); // ��ʼ��ui��

	// varriable
	//PartenerView* hero;

	CREATE_FUNC(WarScene);


private:
	CCNode* mLayerBg; // ������
	CCNode* mLayerEntity; // ʵ���
	CCNode* mLayerEffect; // Ч����
	CCNode* mLayerUI; // UI��

	UILayer* mBgUILayer;

	float mTouchX; // ����ʱx
	float mBeforX; // �ƶ�ǰx

	UIWidget* mSkillBar; // �����������

	CCArray* touchEntityArr;
	PersonView* mTouchEntity;

	CCArray* mSkillBtnArr; // ���ܰ�ť����
	CCArray* mHeadBtnArr; // ͷ������

	//PartenerView* stone; // �����ã��̶�Ŀ�꣬����

	// function
	PersonView* getTargetBySelfPos(int selfType, int selfPos);
};

