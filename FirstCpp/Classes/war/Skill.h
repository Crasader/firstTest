//-----------------------------------------------------------------------------------------------------------------------------
// ����: ����
// ����: lvxiangsong
// ����: 2013-10-8
// ����: ����
// �汾: 
//
// �޸���           ����	           ����		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "cocos2d.h"
#include "PersonView.h"
#include "WarScene.h"

USING_NS_CC;

class Skill : public CCNode
{
public:
	Skill();
	~Skill();

	CREATE_FUNC(Skill);
	bool init();
	void update(float delta);
	void onEnter();
	void onExit();

	void initSkill(int id, CCNode* fromNode, CCNode* toNode);

private:
	CCArmature* mAvatar; // ����
	PersonView* mFromNode; // ������
	PersonView* mToNode; // ��������

	int mId;

	void setAvatar(CCArmature* avatar); // ��������
	void onAnimationComplete(CCArmature * arm, MovementEventType etype, const char * ename); // ���������������
};
