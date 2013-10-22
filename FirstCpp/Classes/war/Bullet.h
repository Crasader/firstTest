#pragma once

#include "cocos2d.h"
#include "PartenerView.h"
#include "PersonView.h"
#include "WarModel.h"

USING_NS_CC;

class Bullet : public CCNode
{
public:
	Bullet(void);
	~Bullet(void);

	CREATE_FUNC(Bullet);
	virtual bool init();
	virtual void update(float delta);
	virtual void onEnter();
	virtual void onExit();

	virtual void initBullet(int id, CCNode* parent, CCNode* fromNode, CCNode* toNode);
protected:
	CCArmature* mAvatar; // ����

	int mId;

	CCNode* mParent;
	PersonView* mFromNode; // ������
	PersonView* mToNode; // ��������

	void setAvatar(CCArmature* avatar); // ��������
	void onAnimationComplete(CCArmature * arm, MovementEventType etype, const char * ename); // ���������������
	void moveComplete(); // �ӵ��ƶ�����
	void scaleComplete(); // ��ʼ�α����
	void delayComplete(); // ��ʱ��������

};