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
		CCRect trect = CCRectApplyAffineTransform(armature->boundingBox(), armature->nodeToParentTransform()); // 获取模型的大小
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
	mAvatar->getAnimation()->play(STATE_STAND);
}

// 设置控制器
void PersonView::setController(ControllerBase* controller)
{
	removeController(); // 先释放掉原先的控制器
	mController = controller;
	controller->setControllerListener(this);
	addChild(controller);
	float sp = (float)mConfig->speed() / 10;
	controller->setSpeed(sp);
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

// 改变方向
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

// 获取方向
PERSON_DIRECTION PersonView::getDirection()
{
	return mDirection;
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

	if (mCurState == ATTACK && state == EMBATTLED) return; // 在攻击动作时，不播放被攻击动画 
	if (mCurState == DIE && state != DIE) return; // 播放死亡动画时，不播放别的动画

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
	changeState(DIE);
	CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_WAR_ENTITY_DIE, this);
}

// 获取自身
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

//触摸事件
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
// 触摸结束事件
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