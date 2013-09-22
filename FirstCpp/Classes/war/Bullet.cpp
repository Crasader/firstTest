#include "Bullet.h"

Bullet::Bullet(void)
{

}

Bullet::~Bullet(void)
{

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
void Bullet::initBullet(int id, CCNode* parent, CCPoint& fromPos, CCNode* toNode)
{
	mId = id;
	mParent = parent;
	mFromPos = fromPos;
	mToNode = toNode;

	// ͨ��id�����в�ѯ�ӵ��ľ���������Ϣ
	CCArmature* av = CCArmature::create("Weapon");
	av->getAnimation()->playByIndex(0);
	setAvatar(av);

	setPosition(fromPos);
	parent->addChild(this);

	scheduleUpdate();
}