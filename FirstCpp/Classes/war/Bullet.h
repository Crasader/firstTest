//-----------------------------------------------------------------------------------------------------------------------------
// ����: �ӵ�
// ����: lvxiangsong
// ����: 2013-10-8
// ����: �ӵ�
// �汾: 
//
// �޸���           ����	           ����		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "cocos2d.h"
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

	virtual void initBullet(int id, CCNode* fromNode, CCNode* toNode);
protected:
	CCArmature* mAvatar; // ����

	int mId;

	PersonView* mFromNode; // ������
	PersonView* mToNode; // ��������

	void setAvatar(CCArmature* avatar); // ��������
	void onAnimationComplete(CCArmature * arm, MovementEventType etype, const char * ename); // ���������������
	void moveComplete(); // �ӵ��ƶ�����
	void scaleComplete(); // ��ʼ�α����
	void delayComplete(); // ��ʱ��������

	bool checkEntity();
};