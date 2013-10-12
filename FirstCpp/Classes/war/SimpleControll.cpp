#include "SimpleControll.h"


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
		actionSpeedX = (targetPos.x - pos.x) / distance * mSpeed;
		actionSpeedY = (targetPos.y - pos.y) / distance * mSpeed;
		if (actionSpeedX != 0) mControllerLintoner->changeDirection(actionSpeedX > 0 ? DIR_RIGHT : DIR_LEFT);
		mControllerLintoner->changeState(RUN);
	}
	else
	{
		// 走路停下来
		actionSpeedX = 0;
		actionSpeedY = 0;
		//mControllerLintoner->changeState(STAND);
	}

	if (actionSpeedX == 0 && actionSpeedY == 0)
	{
		
	}
}

void SimpleControll::checkTargetPos()
{
	if (mControllerLintoner->getTarget() != NULL)
	{
		CCPoint pos = mControllerLintoner->getCurPostion();
		float tempX = pos.x;
		float tempY = pos.y;
		if (fabs(pos.y - mControllerLintoner->getTarget()->getPositionY()) > 5)
		{
			tempY = mControllerLintoner->getTarget()->getPositionY();
		}
		if (pos.x - mControllerLintoner->getTarget()->getPositionX() > 300)
		{
			tempX = mControllerLintoner->getTarget()->getPositionX() + 300;
		}
		else if (pos.x - mControllerLintoner->getTarget()->getPositionX() < -300)
		{
			tempX = mControllerLintoner->getTarget()->getPositionX() - 300;
		}
		if (tempX != pos.x || tempY != pos.y)
		{
			moveTo(CCPoint(tempX, tempY)); // 跑到能打到目标的地方
		}

		// 根据目标位置设置自己的朝向
		if (tempY != pos.x)
		{
			if (mControllerLintoner->getDirection() == DIR_LEFT && pos.x < mControllerLintoner->getTarget()->getPositionX())
			{
				mControllerLintoner->changeDirection(DIR_RIGHT);
			}
			else if (mControllerLintoner->getDirection() == DIR_RIGHT && pos.x > mControllerLintoner->getTarget()->getPositionX())
			{
				mControllerLintoner->changeDirection(DIR_LEFT);
			}
		}
	}
}

void SimpleControll::useSkill(int skillId)
{
	Bullet* bul = Bullet::create();
	bul->initBullet(skillId, CCDirector::sharedDirector()->getRunningScene(), mControllerLintoner->getSelfEntity(), mControllerLintoner->getTarget());
}

void SimpleControll::simpleAttack(float dt)
{
	if (mControllerLintoner->getTarget() == NULL)
	{
		return; // 如果没有目标则不攻击；
	}
	if (mControllerLintoner->getState() != RUN)
	{
		mControllerLintoner->changeState(ATTACK);
		useSkill(1);
	}
}

int SimpleControll::beAttack(float aValue)
{
	mControllerLintoner->changeState(EMBATTLED);
	int result = aValue - mControllerLintoner->getSelfInfo()->defense;
	mControllerLintoner->getSelfInfo()->hp -= result;
	if (mControllerLintoner->getSelfInfo()->hp <= 0)
	{
		mControllerLintoner->dieOut();
	}
	return result;
}