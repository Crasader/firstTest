#pragma once

#include "cocos2d.h"
#include "PartenerView.h"
#include "PersonView.h"
#include "WarModel.h"

USING_NS_CC;

class Bullet : public CCNode
{
public:
	Bullet(void);
	~Bullet(void);

	CREATE_FUNC(Bullet);
	virtual bool init();
	virtual void update(float delta);
	virtual void onEnter();
	virtual void onExit();

	virtual void initBullet(int id, CCNode* parent, CCNode* fromNode, CCNode* toNode);
protected:
	CCArmature* mAvatar; // 形象

	int mId;

	CCNode* mParent;
	PersonView* mFromNode; // 攻击方
	PersonView* mToNode; // 被攻击方

	void setAvatar(CCArmature* avatar); // 设置形象
	void onAnimationComplete(CCArmature * arm, MovementEventType etype, const char * ename); // 单个动画播放完毕
	void moveComplete(); // 子弹移动结束
	void scaleComplete(); // 初始形变结束
	void delayComplete(); // 延时动作结束

};