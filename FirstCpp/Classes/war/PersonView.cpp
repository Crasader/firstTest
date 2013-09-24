#include "PersonView.h"


PersonView::PersonView(void):mTarget(NULL), mAvatar(NULL), mController(NULL), mCurState(STAND)
{
	mInfo = PersonVo::create();
	CC_SAFE_RETAIN(mInfo);
}


PersonView::~PersonView(void)
{
	CC_SAFE_RELEASE_NULL(mInfo);
}

// 设置形象
void PersonView::setAvatar(CCArmature* avatar)
{
	if (mAvatar != NULL)
	{
		removeChild(mAvatar, true);
		mAvatar = 0;
	}
	mAvatar = avatar;
	mAvatar->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(PersonView::onAnimationComplete));
	addChild(mAvatar, 0);
}

// 设置控制器
void PersonView::setController(ControllerBase* controller)
{
	removeController(); // 先释放掉原先的控制器
	mController = controller;
	controller->setControllerListener(this);
	addChild(controller);
}

// 获取控制器
ControllerBase* PersonView::getController()
{
	return (ControllerBase*)mController;
}

// 移除控制器
void PersonView::removeController()
{
	if (mController != NULL)
	{
		removeChild(mController);
		mController = 0;
	}
}

// 设置位置
void PersonView::setSimplePostion(float x, float y)
{
	setPosition(ccp(x, y));
}

// 获取位置
CCPoint PersonView::getCurPostion()
{
	return getPosition();
}

//设置进攻的目标
void PersonView::setTarget(CCNode* target)
{
	mTarget = target;
}

// 是否有进攻目标
bool PersonView::isTarget() const
{
	return mTarget != NULL;
}

// 移除进攻目标
CCNode* PersonView::removeTarget()
{
	CCNode* temp = mTarget;
	mTarget = NULL;
	return temp;
}

void PersonView::changeDirection(PERSON_DIRECTION dir)
{
	switch (dir)
	{
	case DIR_LEFT:
		mAvatar->setScaleX(-1);
		break;
	case DIR_RIGHT:
		mAvatar->setScaleX(1);
		break;
	}
}

// 获取进攻目标
CCNode* PersonView::getTarget()
{
	return mTarget;
}

// 改变状态
void PersonView::changeState(PERSON_STATE state)
{
	if (mAvatar == NULL) return;
	if (mCurState == state) return;

	mCurState = state;

	switch (state)
	{
	case STAND:
		mAvatar->getAnimation()->playByIndex(0);
		break;
	case RUN:
		mAvatar->getAnimation()->playByIndex(1);
		break;
	}
}

// 设置基本信息
void PersonView::setInfo(PersonVo* info)
{
	if (mInfo != NULL)
	{
		CC_SAFE_RELEASE_NULL(mInfo);
	}
	mInfo = info;
	mInfo->retain();
}

// 获取基本信息
PersonVo* PersonView::getInfo() const
{
	return mInfo;
}

// 一个动作播放完毕
void PersonView::onAnimationComplete(CCArmature * arm, MovementEventType etype, const char * ename)
{
	if (etype == COMPLETE)
	{
		if (strcmp(ename, "fwrun") == 0)
		{

		}
		else
		{
			//mAvatar->getAnimation()->playByIndex(1);
			changeState(RUN);
		}
	}
}

// 获取当前状态
PERSON_STATE PersonView::getState()
{
	return mCurState;
}

PersonVo* PersonView::getSelfInfo()
{
	return mInfo;
}

// 死出去
void PersonView::dieOut()
{
	removeFromParent();
}

// 获取自身
CCNode* PersonView::getSelfEntity()
{
	return this;
}