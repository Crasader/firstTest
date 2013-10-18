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
	scheduleUpdate(); // ������ʱ��
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
		schedule(schedule_selector(SimpleControll::simpleAttack), 2.0f); // ͣ������ʼ��⹥��
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
		// ��·ͣ����
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
	PersonView* temptarget = (PersonView*)mControllerLintoner->getTarget();
	PersonView* self = (PersonView*)mControllerLintoner->getSelfEntity();
	AvatarAsset* con;
	config_manager_gettile(AvatarAssetTable, AvatarAsset, CONFIG_AvatarAsset, self->getBaseId(), con);
	int dist = con->distance();
	if (temptarget != NULL)
	{
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
			moveTo(CCPoint(tempX, tempY)); // �ܵ��ܴ�Ŀ��ĵط�
		}

		// ����Ŀ��λ�������Լ��ĳ���
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
	Bullet* bul = Bullet::create();
	bul->initBullet(skillId, CCDirector::sharedDirector()->getRunningScene(), mControllerLintoner->getSelfEntity(), mControllerLintoner->getTarget());
}

void SimpleControll::simpleAttack(float dt)
{
	if (mControllerLintoner->getTarget() == NULL)
	{
		return; // ���û��Ŀ���򲻹�����
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