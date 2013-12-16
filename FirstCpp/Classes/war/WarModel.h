//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 战斗场景数据model
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 战斗场景数据model
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "cocos2d.h"
#include "PersonView.h"

USING_NS_CC;

class WarModel : public CCObject
{
public:
	WarModel(void);
	~WarModel(void);

	virtual bool init();
	static WarModel* shardWarModel();
	static void pure();

	CCArray* getPartenerArray(); // 获取我方数据
	CCArray* getEnemyArray(); // 获取地方数据
	//CCArray* getDieArray();

	void removeEntity(CCObject* entity); // 移除一个实例
	bool isDie(PersonView* obj);

protected:
	CCArray* mPartenerArray; // 我方阵营
	CCArray* mEnemyArray; // 地方阵营
	//CCArray* mDieArray; // 存放已死亡对象
};

