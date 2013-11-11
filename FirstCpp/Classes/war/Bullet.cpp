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

	mId = 0;
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

// 设置形象
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

// 初始化子弹
void Bullet::initBullet(int id, CCNode* parent, CCNode* fromNode, CCNode* toNode)
{
	mId = id;
	mParent = parent;
	mFromNode = (PersonView*)fromNode;
	mToNode = (PersonView*)toNode;

	// 如果id为0，则表示没有子弹动画, 不进行动画处理
	if (id == 0)
	{
		mAvatar = NULL;
		parent->addChild(this);
		CCFiniteTimeAction* mv = CCSequence::create(
			CCDelayTime::create(0.5f),
			CCCallFunc::create(this, callfunc_selector(Bullet::delayComplete)),
			NULL);

		runAction(mv);
		return;
	}
	
	// 通过id到表中查询子弹的具体数据信息
	CCArmature* av = CCArmature::create("Weapon");
	av->getAnimation()->playByIndex(0);
	setAvatar(av);

	int prx = fromNode->getPositionX() < toNode->getPositionX() ? mFromNode->getConfig()->bulletx() : -mFromNode->getConfig()->bulletx();
	setPosition(CCPoint(mFromNode->getPositionX() + prx, mFromNode->getPositionY() + mFromNode->getConfig()->bullety()));
	parent->addChild(this);

	//mAvatar->getAnimation()->play("atteck");
	//return;

	this->setScale(0.2);

	// 子弹移动动画
	CCFiniteTimeAction* mv = CCSequence::create(
		CCScaleTo::create(0.6, 1, 1),
		CCCallFunc::create(this, callfunc_selector(Bullet::scaleComplete)),
		NULL);

	runAction(mv);
}

void Bullet::scaleComplete()
{
	// 子弹移动动画
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

void Bullet::delayComplete()
{
	if (mToNode != NULL && mFromNode != NULL)
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

// 一个动作播放完毕
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
			//removeFromParent(); // 从父对象移除
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
