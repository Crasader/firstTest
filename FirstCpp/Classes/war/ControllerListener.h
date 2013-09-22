#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum PERSON_DIRECTION{DIR_LEFT = 0, DIR_RIGHT = 1};
enum PERSON_STATE{STAND = 0, RUN = 1, ATTACK_ONE = 2};

class ControllerListener
{
public:
	ControllerListener(void);
	~ControllerListener(void);

	virtual void setSimplePostion(float x, float y) = 0;
	virtual CCPoint getCurPostion() = 0;
	virtual void changeDirection(PERSON_DIRECTION dir) = 0;
	virtual CCNode* getTarget() = 0;
	virtual void changeState(PERSON_STATE state) = 0;
	virtual PERSON_STATE getState() = 0;
};

