#pragma once

#include "cocos2d.h"
#include "ControllerListener.h"

USING_NS_CC;

class ControllerBase : public CCNode
{
public:
	ControllerBase(void);
	~ControllerBase(void);

	void setControllerListener(ControllerListener* controllerListener);
	virtual void moveTo(CCPoint targetPos);
	virtual void checkTargetPos() = 0; // �����빥��Ŀ����룬���������ڹ�����Χ��Ҫǰ��
	virtual void stopMove() = 0;

	virtual int beAttack(float aValue) = 0; // ������������Ϊ������

protected:
	ControllerListener* mControllerLintoner;
};

