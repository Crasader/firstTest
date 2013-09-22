#pragma once

#include "cocos2d.h"
#include "PartenerView.h"

USING_NS_CC;

class Bullet : public CCNode
{
public:
	Bullet(void);
	~Bullet(void);

	CREATE_FUNC(Bullet);
	virtual bool init();
	virtual void update(float delta);

	virtual void initBullet(int id, CCNode* parent, CCPoint& fromPos, CCNode* toNode);
protected:
	CCArmature* mAvatar; // 形象

	int mId;

	CCNode* mParent;
	CCPoint mFromPos;
	CCNode* mToNode;

	void setAvatar(CCArmature* avatar); // 设置形象
};