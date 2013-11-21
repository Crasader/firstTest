#include "SimpleControll.h"
#include <stdlib.h>
#include <time.inl>
#include "Skill.h"


SimpleControll::SimpleControll(void)
{
}


SimpleControll::~SimpleControll(void)
{
}

bool SimpleControll::init()
{
	mSpeed = 0;
	targetX = 0;
	targetY = 0;
	actionSpeedX = 0;
	actionSpeedY = 0;
	scheduleUpdate(); // 开启计时器
	return true;
}

void SimpleControll::update(float dt)
{
	if (mControllerLintoner == NULL)
	{
		return;
	}

	if (actionSpeedX == 0 && actionSpeedY == 0)
	{
		return;
	}

	CCPoint pos = mControllerLintoner->getCurPostion();
	if (targetX == pos.x && targetY == pos.y)
	{
		actionSpeedX = 0;
		actionSpeedY = 0;
		mControllerLintoner->changeState(STAND);
		unschedule(schedule_selector(SimpleControll::simpleAttack));
		schedule(schedule_selector(SimpleControll::simpleAttack), 2.0f); // 停下来开始检测攻击
		return;
	}

	if (fabs(targetX - pos.x) > fabs(actionSpeedX))
	{
		pos.x += actionSpeedX;
	}
	else
	{
		pos.x = targetX;
	}

	if (fabs(targetY - pos.y) > fabs(actionSpeedY))
	{
		pos.y += actionSpeedY;
	}
	else
	{
		pos.y = targetY;
	}
	mControllerLintoner->setSimplePostion(pos.x, pos.y);
}

void SimpleControll::setSpeed(float speed = 0)
{
	mSpeed = speed;
}

void SimpleControll::moveTo(CCPoint targetPos)
{
	targetX = targetPos.x;
	targetY = targetPos.y;
	CCPoint pos = mControllerLintoner->getCurPostion();
	float distance = (ccpDistance(targetPos, pos));
	if (distance > 0)
	{
		//
		if (mControllerLintoner->getState() == EMBATTLED || mControllerLintoner->getState() == DIE)
		{

		}
		else
		{
			actionSpeedX = (targetPos.x - pos.x) / distance * mSpeed;
			actionSpeedY = (targetPos.y - pos.y) / distance * mSpeed;
			if (actionSpeedX != 0) mControllerLintoner->changeDirection(actionSpeedX > 0 ? DIR_RIGHT : DIR_LEFT);
			mControllerLintoner->changeState(RUN);
		}
	}
	else
	{
		// 走路停下来
		stopMove();
	}

	if (actionSpeedX == 0 && actionSpeedY == 0)
	{
		
	}
}

void SimpleControll::stopMove()
{
	actionSpeedX = 0;
	actionSpeedY = 0;
}

void SimpleControll::checkTargetPos()
{
	PersonView* temptarget = (PersonView*)mControllerLintoner->getTarget();
	PersonView* self = (PersonView*)mControllerLintoner->getSelfEntity();
	
	if (WarModel::shardWarModel()->isDie(temptarget)) return;
	if (WarModel::shardWarModel()->isDie(self)) return;

	if (temptarget != NULL)
	{
		AvatarAsset* targetConfig = temptarget->getConfig();
		AvatarAsset* selfConfig = self->getConfig();
		int dist = temptarget != NULL ? selfConfig->distance() + targetConfig->bodywidth() : selfConfig->distance();

		CCPoint pos = mControllerLintoner->getCurPostion();
		float tempX = pos.x;
		float tempY = pos.y;
		if (fabs(pos.y - temptarget->getPositionY()) > 10)
		{
			tempY = temptarget->getPositionY();
		}
		if (pos.x - temptarget->getPositionX() > dist)
		{
			tempX = temptarget->getPositionX() + dist;
		}
		else if (pos.x - temptarget->getPositionX() < -dist)
		{
			tempX = temptarget->getPositionX() - dist;
		}
		if (tempX != pos.x || tempY != pos.y)
		{
			moveTo(CCPoint(tempX, tempY)); // 跑到能打到目标的地方
		}

		// 根据目标位置设置自己的朝向
		if (tempY != pos.x)
		{
			if (mControllerLintoner->getDirection() == DIR_LEFT && pos.x < temptarget->getPositionX())
			{
				mControllerLintoner->changeDirection(DIR_RIGHT);
			}
			else if (mControllerLintoner->getDirection() == DIR_RIGHT && pos.x > temptarget->getPositionX())
			{
				mControllerLintoner->changeDirection(DIR_LEFT);
			}
		}
	}
}

void SimpleControll::useSkill(int skillId)
{
	if (mControllerLintoner->getTarget() == NULL) return;
	if (WarModel::shardWarModel()->isDie((PersonView*)mControllerLintoner->getTarget()))
	{
		((PersonView*)mControllerLintoner->getSelfEntity())->setTarget(NULL);
		return;
	}

	unschedule(schedule_selector(SimpleControll::simpleAttack));
	mControllerLintoner->changeState(SKILL);

	Bullet* bul = Bullet::create();
	bul->initBullet(skillId, mControllerLintoner->getSelfEntity(), mControllerLintoner->getTarget());

	Skill* skill = Skill::create();
	skill->initSkill(skillId, mControllerLintoner->getSelfEntity(), mControllerLintoner->getTarget());
	schedule(schedule_selector(SimpleControll::simpleAttack), 2.0f); // 停下来开始检测攻击
}

void SimpleControll::simpleAttack(int dt)
{
	if (mControllerLintoner->getTarget() == NULL)
	{
		return; // 如果没有目标则不攻击；
	}
	else
	{
		PersonView* tempTarget = (PersonView*)(mControllerLintoner->getTarget());
		if (WarModel::shardWarModel()->isDie(tempTarget) || tempTarget->getState() == DIE)
		{
			((PersonView*)mControllerLintoner->getSelfEntity())->setTarget(NULL);
			return;
		}
	}
	if (mControllerLintoner->getState() != RUN)
	{
		std::srand(time(0));
		mControllerLintoner->changeState(ATTACK);
		Bullet* bul = Bullet::create();
		bul->initBullet(0, mControllerLintoner->getSelfEntity(), mControllerLintoner->getTarget());
	}
}

int SimpleControll::beAttack(int aValue)
{
	mControllerLintoner->changeState(EMBATTLED);
	int result = aValue - mControllerLintoner->getSelfInfo()->defense;
	if (result < 0) result = 1;
	mControllerLintoner->getSelfInfo()->hp -= result;
	if (!mControllerLintoner->checkHp())
	{
		mControllerLintoner->dieOut();
	}
	return result;
}