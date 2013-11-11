#pragma once
#include "controllerbase.h"
#include "cocos2d.h"
#include "Bullet.h"
#include "ConfigManager.h"

USING_NS_CC;

class SimpleControll :
	public ControllerBase
{
public:
	SimpleControll(void);
	~SimpleControll(void);

	CREATE_FUNC(SimpleControll);
	virtual bool init();
	virtual void update(float dt);

	virtual void setSpeed(float speed);
	virtual void moveTo(CCPoint targetPos);
	virtual void checkTargetPos();
	virtual void stopMove();

	void useSkill(int skillId); // 使用技能
	void simpleAttack(int dt); // 普通攻击
	

	virtual int beAttack(int aValue); // 遭受攻击

protected:
	float mSpeed; // 速度
	float actionSpeedX; // x方向执行速度
	float actionSpeedY; // y方向执行速度
	float targetX; // 目标点x
	float targetY; // 目标点y

};

