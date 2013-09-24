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
	//mAvatar->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(PersonView::onAnimationComplete));
	addChild(mAvatar, 0);
}

// ��ʼ���ӵ�
void Bullet::initBullet(int id, CCNode* parent, CCNode* fromNode, CCNode* toNode)
{
	mId = id;
	mParent = parent;
	mFromNode = fromNode;
	mToNode = toNode;

	// ͨ��id�����в�ѯ�ӵ��ľ���������Ϣ
	CCArmature* av = CCArmature::create("Weapon");
	av->getAnimation()->playByIndex(0);
	setAvatar(av);

	setPosition(mFromNode->getPosition());
	parent->addChild(this);

	// �ӵ��ƶ�����
	CCFiniteTimeAction* mv = CCSequence::create(
		CCMoveTo::create(0.2, toNode->getPosition()),
		CCCallFunc::create(this, callfunc_selector(Bullet::moveComplete)),
		NULL);

	runAction(mv);
}

void Bullet::moveComplete()
{
	if (mToNode != NULL)
	{
		((PartenerView*)mToNode)->getController()->beAttack(260.0f);
		if (((PartenerView*)mToNode)->getSelfInfo()->hp <= 0)
		{
			((PersonView*)mFromNode)->setTarget(NULL);
			WarModel::shardWarModel()->removeEntity(mToNode);
		}
	}
	removeFromParent(); // �Ӹ������Ƴ�
}