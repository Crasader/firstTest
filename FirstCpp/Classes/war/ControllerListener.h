#pragma once

#include "cocos2d.h"
#include "PersonVo.h"

USING_NS_CC;

enum PERSON_DIRECTION{DIR_LEFT = 0, DIR_RIGHT = 1};
enum PERSON_STATE{STAND = 0, SKILL, RUN, EMBATTLED, ATTACK, DIE};

class ControllerListener
{
public:
	ControllerListener(void);
	~ControllerListener(void);

	virtual void setSimplePostion(float x, float y) = 0;
	virtual CCPoint getCurPostion() = 0;
	virtual void changeDirection(PERSON_DIRECTION dir) = 0;
	virtual PERSON_DIRECTION getDirection() = 0;
	virtual CCNode* getTarget() = 0;
	virtual CCNode* getSelfEntity() = 0;
	virtual void changeState(PERSON_STATE state) = 0;
	virtual PERSON_STATE getState() = 0;
	virtual PersonVo* getSelfInfo() = 0;
	virtual void dieOut() = 0;
	virtual bool checkHp() = 0;
};

