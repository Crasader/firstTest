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

// 设置形象
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

// 初始化子弹
void Bullet::initBullet(int id, CCNode* parent, CCPoint& fromPos, CCNode* toNode)
{
	mId = id;
	mParent = parent;
	mFromPos = fromPos;
	mToNode = toNode;

	// 通过id到表中查询子弹的具体数据信息
	CCArmature* av = CCArmature::create("Weapon");
	av->getAnimation()->playByIndex(0);
	setAvatar(av);

	setPosition(fromPos);
	parent->addChild(this);

	scheduleUpdate();
}