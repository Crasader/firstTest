#include "Skill.h"

Skill::Skill()
{

}

Skill::~Skill()
{

}

void Skill::onEnter()
{
	CCNode::onEnter();

	scheduleUpdate();
}

void Skill::onExit()
{
	unscheduleUpdate();
	stopAllActions();
	CCNode::onExit();
}

bool Skill::init()
{
	return true;
}

void Skill::update(float delta)
{

}

// 设置形象
void Skill::setAvatar(CCArmature* avatar)
{
	if (mAvatar != NULL)
	{
		removeChild(mAvatar, true);
		mAvatar = 0;
	}
	mAvatar = avatar;
	mAvatar->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(Skill::onAnimationComplete));
	addChild(mAvatar, 0);
}

void Skill::initSkill(int id, CCNode* fromNode, CCNode* toNode)
{
	mId = id;
	mFromNode = (PersonView*)fromNode;
	mToNode = (PersonView*)toNode;
}

// 一个动作播放完毕
void Skill::onAnimationComplete(CCArmature * arm, MovementEventType etype, const char * ename)
{
	if (etype == COMPLETE || etype == LOOP_COMPLETE)
	{

	}
}
