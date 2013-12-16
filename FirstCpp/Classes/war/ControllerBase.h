//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 控制器基类
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 控制器基类
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "cocos2d.h"
#include "ControllerListener.h"

USING_NS_CC;

class ControllerBase : public CCNode
{
public:
	ControllerBase(void);
	virtual ~ControllerBase(void);

	void setControllerListener(ControllerListener* controllerListener);
	virtual void moveTo(CCPoint targetPos);
	virtual void checkTargetPos() = 0; // 检测距离攻击目标距离，如果距离大于攻击范围则要前进
	virtual void stopMove() = 0;
	virtual void setSpeed(float speed) = 0;

	virtual int beAttack(int aValue) = 0; // 被攻击，参数为攻击力
	virtual bool useSkill(int skillId) = 0;

protected:
	ControllerListener* mControllerLintoner;
};

