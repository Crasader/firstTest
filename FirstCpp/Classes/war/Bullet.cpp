#include "Bullet.h"

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
		mAvatar->removeFromParent();
		mAvatar = NULL;
	}

	mId = NULL;
	mParent = NULL;
	mFromNode = NULL;
	mToNode = NULL;

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
void Bullet::initBullet(int id, CCNode* parent, CCNode* fromNode, CCNode* toNode)
{
	mId = id;
	mParent = parent;
	mFromNode = (PersonView*)fromNode;
	mToNode = (PersonView*)toNode;

	// ͨ��id�����в�ѯ�ӵ��ľ���������Ϣ
	CCArmature* av = CCArmature::create("Weapon");
	av->getAnimation()->playByIndex(0);
	setAvatar(av);

	int prx = fromNode->getPositionX() < toNode->getPositionX() ? 35 : -35;
	setPosition(CCPoint(mFromNode->getPositionX() + prx, mFromNode->getPositionY() + 60));
	parent->addChild(this);

	//mAvatar->getAnimation()->play("atteck");
	//return;

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
	CCFiniteTimeAction* mv = CCSequence::create(
		CCMoveTo::create(0.2, CCPoint(mToNode->getPositionX(), mToNode->getPositionY() + 50)),
		CCCallFunc::create(this, callfunc_selector(Bullet::moveComplete)),
		NULL);
	runAction(mv);
}

void Bullet::moveComplete()
{
	((PartenerView*)mToNode)->getController()->beAttack(260.0f);
	
	mAvatar->getAnimation()->play("atteck");
	
}

// һ�������������
void Bullet::onAnimationComplete(CCArmature * arm, MovementEventType etype, const char * ename)
{
	if (etype == COMPLETE || etype == LOOP_COMPLETE)
	{
		if (strcmp(ename, "atteck") == 0)
		{
			if (mToNode != NULL)
			{
				if (((PartenerView*)mToNode)->getSelfInfo()->hp <= 0)
				{
					((PersonView*)mFromNode)->setTarget(NULL);
					WarModel::shardWarModel()->removeEntity(mToNode);
				}
			}
			mAvatar->removeFromParentAndCleanup(true);
			mAvatar = NULL;
			//removeFromParent(); // �Ӹ������Ƴ�
			removeFromParentAndCleanup(true);
		}
		else
		{
			
		}
	}
	else
	{
		if (strcmp(ename, "atteck") == 0)
		{
			CCLog("attack start");
		}
	}
}