//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 战斗模型数据
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 战斗模型数据
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include <string>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class PersonVo: public CCObject
{
public:

	PersonVo(void);
	virtual ~PersonVo(void);

	CREATE_FUNC(PersonVo);
	virtual bool init();
	CCArray* getSkillArr() const;

	string name;
	int posId;
	int gender;
	string pngName;
	string xmlName;
	string jsonName;

	int hp;
	int maxHp;
	int attack;
	int maxattack;
	int defense;
	float attackDelay;

	CCArray* skillArr;

	int simpleBullet; // 普通攻击子弹id
};