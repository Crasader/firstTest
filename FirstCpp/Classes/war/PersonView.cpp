#include "PersonView.h"
#include "ConfigManager.h"
#include <map>
#include "WarScene.h"
#include "EnumEvent.h"
#include "EnumCommon.h"

static std::map<int, AvatarAsset*> avatarMap;

PersonView::PersonView(void):mTarget(NULL), mAvatar(NULL), mController(NULL), mCurState(STAND), mDirection(DIR_RIGHT), mConfig(NULL), 
	mBloodBar(NULL)
{
	mInfo = PersonVo::create();
	CC_SAFE_RETAIN(mInfo);
}


PersonView::~PersonView(void)
{
	mConfig = NULL;
	CC_SAFE_RELEASE_NULL(mInfo);
}

void PersonView::pure()
{
	std::map<int, AvatarAsset*>::iterator it;
	for(it = avatarMap.begin(); it != avatarMap.end(); it++)
	{
		delete it->second;
	}
	avatarMap.clear();
}

void PersonView::onEnter()
{
	CCNode::onEnter();
	setTouchEnable(true);
}

void PersonView::onExit()
{
	setTouchEnable(false);

	mAvatar->removeFromParentAndCleanup(true);
	mController->removeFromParentAndCleanup(true);
	mBloodBar->removeFromParentAndCleanup(true);

	CCNode::onExit();
}

void PersonView::setBaseId(int id)
{
	mId = id;

	std::map<int, AvatarAsset*>::iterator it = avatarMap.find(mId);
	if (it == avatarMap.end())
	{
		AvatarAsset* con = NULL;
		config_manager_gettile(AvatarAssetTable, AvatarAsset, CONFIG_AvatarAsset, mId, con);
		mConfig = new AvatarAsset;
		mConfig->CopyFrom(*con);
		avatarMap[mId] = mConfig;
	}
	else
	{
		mConfig = it->second;
	}

	mInfo->hp = mInfo->maxHp = mConfig->hp();
	mInfo->defense = mConfig->defe();
	mInfo->attack = mConfig->att();
	
	CCArmature* armature = CCArmature::create(mConfig->name().c_str());
	setAvatar(armature);

	//if (id == 3)
	//{
	//	CCBone* bone = armature->getBone("staff");
	//	CCSpriteDisplayData displayData;  
	//	displayData.setParam("Pastor-weapon-pastor_staff_1.png");
	//	bone->addDisplay(&displayData, 1);  
	//	bone->changeDisplayByIndex(1, true);
	//}

	if (mBloodBar == NULL)
	{
		mBloodBar = BloodBar::create();
		CCRect trect = CCRectApplyAffineTransform(armature->boundingBox(), armature->nodeToParentTransform()); // ��ȡģ�͵Ĵ�С
		mBloodBar->setPositionY(trect.getMaxY());
		addChild(mBloodBar, 1);
		
	}
}

int PersonView::getBaseId() const
{
	return mId;
}

void PersonView::setTouchEnable(bool value)
{
	if (value) CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
	else CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

AvatarAsset* PersonView::getConfig()
{
	return mConfig;
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
	mAvatar->getAnimation()->play(STATE_STAND);
}

// ���ÿ�����
void PersonView::setController(ControllerBase* controller)
{
	removeController(); // ���ͷŵ�ԭ�ȵĿ�����
	mController = controller;
	controller->setControllerListener(this);
	addChild(controller);
	float sp = (float)mConfig->speed() / 10;
	controller->setSpeed(sp);
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

// �ı䷽��
void PersonView::changeDirection(PERSON_DIRECTION dir)
{
	mDirection = dir;
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

// ��ȡ����
PERSON_DIRECTION PersonView::getDirection()
{
	return mDirection;
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

	if (mCurState == ATTACK && state == EMBATTLED) return; // �ڹ�������ʱ�������ű��������� 
	if (mCurState == DIE && state != DIE) return; // ������������ʱ�������ű�Ķ���

	mCurState = state;

	switch (state)
	{
	case STAND:
		mAvatar->getAnimation()->play(STATE_STAND);
		break;
	case SKILL:
		mAvatar->getAnimation()->play(STATE_SKILL);
		break;
	case RUN:
		mAvatar->getAnimation()->play(STATE_RUN);
		break;
	case EMBATTLED:
		mController->stopMove();
		mAvatar->getAnimation()->play(STATE_EMBATTLED);
		break;
	case ATTACK:
		mAvatar->getAnimation()->play(STATE_ATTACK);
		break;
	case DIE:
		setTouchEnable(false);
		mController->stopMove();
		mAvatar->getAnimation()->play(STATE_DIE);
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
	if (etype == COMPLETE || etype == LOOP_COMPLETE)
	{
		if (strcmp(ename, STATE_RUN) == 0)
		{

		}
		else if (strcmp(ename, STATE_DIE) == 0)
		{
			removeFromParent();
		}
		else
		{
			changeState(STAND);
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
	changeState(DIE);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_WAR_ENTITY_DIE, this);
}

// ��ȡ����
CCNode* PersonView::getSelfEntity()
{
	return this;
}

bool PersonView::checkHp()
{
	if (mInfo->hp < 0) mInfo->hp = 0;
	mBloodBar->setPercentage((float)mInfo->hp / mInfo->maxHp);
	return mInfo->hp == 0 ? false : true;
}

//�����¼�
bool PersonView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (mAvatar != NULL)
	{
		CCSize size = mAvatar->getContentSize();
		float minx = this->getPositionX() - size.width / 2;
		float maxx = this->getPositionX() + size.width / 2;
		float miny = this->getPositionY();
		float maxy = this->getPositionY() + size.height;
		CCPoint touchPoint = pTouch->getLocation();
		if (touchPoint.x > minx && touchPoint.x < maxx && touchPoint.y > miny && touchPoint.y < maxy && mCurState != DIE)
		{
			CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_WAR_ADD_TOUCH_ENTITY, this);
		}
	}
	return true;
}
// ���������¼�
void PersonView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_WAR_ADD_TOUCH_END, this);
}

float PersonView::getContentHeight()
{
	if (mAvatar) return mAvatar->getContentSize().height;
	return 0;
}
float PersonView::getContentWidth()
{
	if (mAvatar) return mAvatar->getContentSize().width;
	return 0;
}