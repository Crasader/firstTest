#include "SimpleControll.h"
#include <stdlib.h>
#include "EnumEvent.h"


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
	mTempDelay = 2.0f;
	return true;
}

void SimpleControll::onEnter()
{
	ControllerBase::onEnter();

	scheduleUpdate(); // 开启计时器
}

void SimpleControll::onExit()
{
	unscheduleUpdate();

	ControllerBase::onExit();
}

void SimpleControll::update(float dt)
{
	if (mControllerLintoner == NULL)
	{
		return;
	}
	CCPoint pos = mControllerLintoner->getCurPostion();
	if (actionSpeedX == 0 && actionSpeedY == 0)
	{
		if (targetX == pos.x && targetY == pos.y)
		{
			return;
		}
		else
		{
			targetX = pos.x;
			targetY = pos.y;
		}
	}

	if (targetX == pos.x && targetY == pos.y)
	{
		stopMove();
		unschedule(schedule_selector(SimpleControll::simpleAttack));
		schedule(schedule_selector(SimpleControll::simpleAttack), mControllerLintoner->getSelfInfo()->attackDelay); // 停下来开始检测攻击
		
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
			//unschedule(schedule_selector(SimpleControll::simpleAttack));
		}
		else
		{
			actionSpeedX = (targetPos.x - pos.x) / distance * mSpeed;
			actionSpeedY = (targetPos.y - pos.y) / distance * mSpeed;
			if (actionSpeedX != 0) mControllerLintoner->changeDirection(actionSpeedX > 0 ? DIR_RIGHT : DIR_LEFT);
			mControllerLintoner->changeState(RUN);
			
		}
	}
}

void SimpleControll::stopMove()
{
	mControllerLintoner->changeState(STAND);
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
		CCPoint pos = mControllerLintoner->getCurPostion();
		float tempX = pos.x;
		float tempY = pos.y;

		int dist = fabs(pos.y - temptarget->getPositionY()) < 10 ? selfConfig->distance() + targetConfig->bodywidth() + selfConfig->bodywidth() : selfConfig->distance() / 1.414;
		float maxDis = pos.getDistance(temptarget->getPosition());

		if (maxDis > dist)
		{
			float dt = (maxDis - dist) / maxDis;
			tempX += (temptarget->getPositionX() - tempX) * dt;
			tempY += (temptarget->getPositionY() - tempY) * dt;
		}
		if (selfConfig->isremote() == 0 && fabs(pos.y - temptarget->getPositionY()) > 20)
		{
			tempY = temptarget->getPositionY();
			if (pos.x - temptarget->getPositionX() >= dist)
			{
				tempX = temptarget->getPositionX() + dist;
			}
			else if (pos.x - temptarget->getPositionX() < -dist)
			{
				tempX = temptarget->getPositionX() - dist;
			}
		}
		/*if (fabs(pos.y - temptarget->getPositionY()) > 10)
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
		}*/
		if (tempX != pos.x || tempY != pos.y)
		{
			moveTo(CCPoint(tempX, tempY)); // 跑到能打到目标的地方
			//if (self->getBaseId() == 1)
			//{
			//	CCLog("(%f,%f),(%f,%f)",tempX,tempY,pos.x,pos.y);
			//}
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

bool SimpleControll::useSkill(int skillId)
{
	if (mControllerLintoner->getTarget() == NULL) return false;
	if (WarModel::shardWarModel()->isDie((PersonView*)mControllerLintoner->getTarget()))
	{
		((PersonView*)mControllerLintoner->getSelfEntity())->setTarget(NULL);
		return false;
	}

	unschedule(schedule_selector(SimpleControll::simpleAttack));
	mControllerLintoner->changeState(SKILL);

	Bullet* bul = Bullet::create();
	bul->initBullet(skillId, mControllerLintoner->getSelfEntity(), mControllerLintoner->getTarget());

	Skill* skill = Skill::create();
	skill->initSkill(skillId, mControllerLintoner->getSelfEntity(), mControllerLintoner->getTarget());
	schedule(schedule_selector(SimpleControll::simpleAttack), mControllerLintoner->getSelfInfo()->attackDelay); // 停下来开始检测攻击

	return true;
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
		mControllerLintoner->changeState(ATTACK);
		Bullet* bul = Bullet::create();
		bul->initBullet(((PersonView*)mControllerLintoner->getSelfEntity())->getBaseId(), 
			mControllerLintoner->getSelfEntity(), 
			mControllerLintoner->getTarget());
	}
	mTempDelay = 0;
}

int SimpleControll::beAttack(int aValue)
{
	mControllerLintoner->changeState(EMBATTLED);
	int result = aValue - mControllerLintoner->getSelfInfo()->defense;
	if (result < 0) result = 1;
	mControllerLintoner->getSelfInfo()->hp -= result;
	if (!mControllerLintoner->checkHp())
	{
		mControllerLintoner->dieOut(); // hp小于0就死出去
	}

	// 创建飘血字
	BloodFont* bft = BloodFont::create();
	PersonView* selfentity = (PersonView*)mControllerLintoner->getSelfEntity();
	float contenth = selfentity->getContentHeight();
	bft->initBloodFont(result,mControllerLintoner->getSelfEntity()->getPositionX(),
		mControllerLintoner->getSelfEntity()->getPositionY() + contenth - 40);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_WAR_SHOW_BLOOD_FONT, bft);
	return result;
}