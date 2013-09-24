#pragma once
#include "controllerbase.h"
#include "cocos2d.h"
#include "Bullet.h"

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

	void setSpeed(float speed);
	virtual void moveTo(CCPoint targetPos);
	virtual void checkTargetPos();

	void useSkill(int skillId); // ʹ�ü���
	void simpleAttack(float dt); // ��ͨ����

	virtual int beAttack(float aValue); // ���ܹ���

protected:
	float mSpeed; // �ٶ�
	float actionSpeedX; // x����ִ���ٶ�
	float actionSpeedY; // y����ִ���ٶ�
	float targetX; // Ŀ���x
	float targetY; // Ŀ���y
};

