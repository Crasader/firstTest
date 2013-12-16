//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 技能
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 技能
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "cocos2d.h"
#include "PersonView.h"
#include "WarScene.h"

USING_NS_CC;

class Skill : public CCNode
{
public:
	Skill();
	~Skill();

	CREATE_FUNC(Skill);
	bool init();
	void update(float delta);
	void onEnter();
	void onExit();

	void initSkill(int id, CCNode* fromNode, CCNode* toNode);

private:
	CCArmature* mAvatar; // 形象
	PersonView* mFromNode; // 攻击方
	PersonView* mToNode; // 被攻击方

	int mId;

	void setAvatar(CCArmature* avatar); // 设置形象
	void onAnimationComplete(CCArmature * arm, MovementEventType etype, const char * ename); // 单个动画播放完毕
};
