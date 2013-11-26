#pragma once

#include "cocos2d.h"
#include "ControllerListener.h"

USING_NS_CC;

class ControllerBase : public CCNode
{
public:
	ControllerBase(void);
	virtual ~ControllerBase(void);

	void setControllerListener(ControllerListener* controllerListener);
	virtual void moveTo(CCPoint targetPos);
	virtual void checkTargetPos() = 0; // �����빥��Ŀ����룬���������ڹ�����Χ��Ҫǰ��
	virtual void stopMove() = 0;
	virtual void setSpeed(float speed) = 0;

	virtual int beAttack(int aValue) = 0; // ������������Ϊ������
	virtual bool useSkill(int skillId) = 0;

protected:
	ControllerListener* mControllerLintoner;
};

