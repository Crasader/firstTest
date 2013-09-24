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

// ��������
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

// ���ÿ�����
void PersonView::setController(ControllerBase* controller)
{
	removeController(); // ���ͷŵ�ԭ�ȵĿ�����
	mController = controller;
	controller->setControllerListener(this);
	addChild(controller);
}

// ��ȡ������
ControllerBase* PersonView::getController()
{
	return (ControllerBase*)mController;
}

// �Ƴ�������
void PersonView::removeController()
{
	if (mController != NULL)
	{
		removeChild(mController);
		mController = 0;
	}
}

// ����λ��
void PersonView::setSimplePostion(float x, float y)
{
	setPosition(ccp(x, y));
}

// ��ȡλ��
CCPoint PersonView::getCurPostion()
{
	return getPosition();
}

//���ý�����Ŀ��
void PersonView::setTarget(CCNode* target)
{
	mTarget = target;
}

// �Ƿ��н���Ŀ��
bool PersonView::isTarget() const
{
	return mTarget != NULL;
}

// �Ƴ�����Ŀ��
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

// ��ȡ����Ŀ��
CCNode* PersonView::getTarget()
{
	return mTarget;
}

// �ı�״̬
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

// ���û�����Ϣ
void PersonView::setInfo(PersonVo* info)
{
	if (mInfo != NULL)
	{
		CC_SAFE_RELEASE_NULL(mInfo);
	}
	mInfo = info;
	mInfo->retain();
}

// ��ȡ������Ϣ
PersonVo* PersonView::getInfo() const
{
	return mInfo;
}

// һ�������������
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

// ��ȡ��ǰ״̬
PERSON_STATE PersonView::getState()
{
	return mCurState;
}

PersonVo* PersonView::getSelfInfo()
{
	return mInfo;
}

// ����ȥ
void PersonView::dieOut()
{
	removeFromParent();
}

// ��ȡ����
CCNode* PersonView::getSelfEntity()
{
	return this;
}