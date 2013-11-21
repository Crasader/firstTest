#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ControllerListener.h"
#include "ControllerBase.h"
#include "PersonVo.h"
#include "proto\AvatarAsset.pb.h"
#include "Component.h"

using namespace cocos2d::extension;

USING_NS_CC;

class PersonView : public CCNode, public CCTargetedTouchDelegate, public ControllerListener
{
public:
	PersonView(void);
	virtual ~PersonView(void);
	virtual void onEnter();
	virtual void onExit();

	// function
	void setAvatar(CCArmature* avatar); // ��������
	void setController(ControllerBase* controller); // ���ÿ�����
	void removeController(); // �Ƴ�������
	virtual ControllerBase* getController(); // ��ȡ������
	void setTarget(CCNode* target); //���ý�����Ŀ��
	bool isTarget() const; // �Ƿ��н���Ŀ��
	CCNode* removeTarget(); // �Ƴ�����Ŀ��
	virtual void setInfo(PersonVo* info); // ���û�����Ϣ
	virtual PersonVo* getInfo() const; // ��ȡ������Ϣ
	void setBaseId(int id); //
	int getBaseId() const;
	void setTouchEnable(bool value);


	//ʵ��ControllerListener�ӿ�
	void setSimplePostion(float x, float y); // ����λ��
	virtual CCPoint getCurPostion(); // ��ȡλ��
	virtual void changeDirection(PERSON_DIRECTION dir); // �ı䷽��
	virtual PERSON_DIRECTION getDirection(); // ��ȡ����
	virtual CCNode* getTarget(); // ��ȡ����Ŀ��
	virtual void changeState(PERSON_STATE state); // �ı�״̬
	virtual PERSON_STATE getState(); // ��ȡ��ǰ״̬
	virtual PersonVo* getSelfInfo(); // ��ȡ��λ��������Ϣ
	virtual void dieOut(); // ����ȥ
	virtual CCNode* getSelfEntity(); // ��ȡ�Լ�
	virtual AvatarAsset* getConfig(); // ��ȡ����
	virtual bool checkHp(); // ���hp

	//��дCCTouchDelegate����
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent); // ������ʼ
	//virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent); // �����ƶ�
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); // ��������

protected:
	AvatarAsset* mConfig; // ��������
	CCArmature* mAvatar; // ����
	ControllerBase* mController; // ������
	CCNode* mTarget; // ������Ŀ��
	PERSON_STATE mCurState; // ��ǰ״̬
	PersonVo* mInfo; // ������Ϣ
	PERSON_DIRECTION mDirection; // ����
	int mId;
	BloodBar* mBloodBar; // Ѫ��
	
	void onAnimationComplete(CCArmature * arm, MovementEventType etype, const char * ename);
	
};

