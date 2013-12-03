#include "Bullet.h"
#include "WarScene.h"
#include "EnumEvent.h"

Bullet::Bullet(void)
{

}

Bullet::~Bullet(void)
{
	
}

void Bullet::onEnter()
{
	CCNode::onEnter();

	scheduleUpdate();
}

void Bullet::onExit()
{
	if (mAvatar != NULL)
	{
		mAvatar->removeFromParentAndCleanup(true);
		mAvatar = NULL;
	}

	mId = 0;
	mFromNode = NULL;
	mToNode = NULL;
	removeAllChildrenWithCleanup(true);
	unscheduleUpdate();
	stopAllActions();
	CCNode::onExit();
}

bool Bullet::init()
{
	return true;
}

void Bullet::update(float delta)
{
	
}

// ��������
void Bullet::setAvatar(CCArmature* avatar)
{
	if (mAvatar != NULL)
	{
		removeChild(mAvatar, true);
		mAvatar = 0;
	}
	mAvatar = avatar;
	mAvatar->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Bullet::onAnimationComplete));
	addChild(mAvatar, 0);
}

// ��ʼ���ӵ�
void Bullet::initBullet(int id, CCNode* fromNode, CCNode* toNode)
{
	if (id == 1 || id == 4 || id == 5 || id == 6) 
		mId = 0;
	else 
		mId = 1;
	mFromNode = (PersonView*)fromNode;
	mToNode = (PersonView*)toNode;

	// ���idΪ0�����ʾû���ӵ�����, �����ж�������
	if (mId == 0)
	{
		mAvatar = NULL;
		CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_WAR_ADD_EFFECT, this);
		CCFiniteTimeAction* mv = CCSequence::create(
			CCDelayTime::create(0.5f),
			CCCallFunc::create(this, callfunc_selector(Bullet::delayComplete)),
			NULL);

		runAction(mv);
		return;
	}
	
	// ͨ��id�����в�ѯ�ӵ��ľ���������Ϣ
	CCArmature* av = CCArmature::create("Bullet");
	av->getAnimation()->playByIndex(0);
	setAvatar(av);

	int prx = fromNode->getPositionX() < toNode->getPositionX() ? mFromNode->getConfig()->bulletx() : -mFromNode->getConfig()->bulletx();
	setPosition(CCPoint(mFromNode->getPositionX() + prx, mFromNode->getPositionY() + mFromNode->getConfig()->bullety()));
	CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_WAR_ADD_EFFECT, this);
	this->setScale(0.2);

	// �ӵ��ƶ�����
	CCFiniteTimeAction* mv = CCSequence::create(
		CCScaleTo::create(0.6, 1, 1),
		CCCallFunc::create(this, callfunc_selector(Bullet::scaleComplete)),
		NULL);

	runAction(mv);
}

void Bullet::scaleComplete()
{
	// �ӵ��ƶ�����
	if (checkEntity())
	{
		CCFiniteTimeAction* mv = CCSequence::create(
			CCMoveTo::create(0.2, CCPoint(mToNode->getPositionX(), mToNode->getPositionY() + 50)),
			CCCallFunc::create(this, callfunc_selector(Bullet::moveComplete)),
			NULL);
		runAction(mv);
	}
}

void Bullet::moveComplete()
{
	if (checkEntity()) 
	{
		((PartenerView*)mToNode)->getController()->beAttack(mFromNode->getInfo()->attack);
	}
	if (mAvatar)
		mAvatar->getAnimation()->play("embattled");
}

void Bullet::delayComplete()
{
	if (checkEntity())
	{
		mToNode->getController()->beAttack(mFromNode->getInfo()->attack);
		if (mToNode->getSelfInfo()->hp <= 0)
		{
			mFromNode->setTarget(NULL);
			WarModel::shardWarModel()->removeEntity(mToNode);
		}
	}
	removeFromParentAndCleanup(true);
}

// һ�������������
void Bullet::onAnimationComplete(CCArmature * arm, MovementEventType etype, const char * ename)
{
	if (etype == COMPLETE || etype == LOOP_COMPLETE)
	{
		if (strcmp(ename, "embattled") == 0)
		{
			if (checkEntity())
			{
				if (mToNode->getSelfInfo()->hp <= 0)
				{
					mFromNode->setTarget(NULL);
					WarModel::shardWarModel()->removeEntity(mToNode);
				}
				mAvatar->removeFromParentAndCleanup(true);
				mAvatar = NULL;
				//removeFromParent(); // �Ӹ������Ƴ�
				removeFromParentAndCleanup(true);
			}
		}
		else
		{
			
		}
	}
	else
	{
		if (strcmp(ename, "embattled") == 0)
		{
			//CCLog("embattled start");
		}
	}
}

bool Bullet::checkEntity()
{
	bool todie = WarModel::shardWarModel()->isDie(mToNode);
	bool fromdie = WarModel::shardWarModel()->isDie(mFromNode);
	
	if (todie && !fromdie)
	{
		mFromNode->setTarget(NULL);
		if (mAvatar != NULL)
		{
			mAvatar->removeFromParentAndCleanup(true);
			mAvatar = NULL;
		}
		removeFromParentAndCleanup(true);
		return false;
	}
	else if (!todie && fromdie)
	{
		if (mAvatar != NULL)
		{
			mAvatar->removeFromParentAndCleanup(true);
			mAvatar = NULL;
		}
		removeFromParentAndCleanup(true);
		return false;
	}
	else if (todie && fromdie)
	{
		if (mAvatar != NULL)
		{
			mAvatar->removeFromParentAndCleanup(true);
			mAvatar = NULL;
		}
		removeFromParentAndCleanup(true);
		return false;
	}
	else
	{
		return true;
	}
}