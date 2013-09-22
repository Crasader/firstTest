#pragma once

#include "cocos2d.h"

USING_NS_CC;

class WarModel : public CCObject
{
public:
	WarModel(void);
	~WarModel(void);

	virtual bool init();
	static WarModel* shardWarModel();

	CCArray* getPartenerArray(); // 获取我方数据
	CCArray* getEnemyArray(); // 获取地方数据

protected:
	CCArray* mPartenerArray; // 我方阵营
	CCArray* mEnemyArray; // 地方阵营
};

