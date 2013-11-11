#pragma once

#include <string>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class PersonVo: public CCObject
{
public:

	PersonVo(void);
	~PersonVo(void);

	CREATE_FUNC(PersonVo);
	virtual bool init();

	string name;
	int posId;
	int gender;
	string pngName;
	string xmlName;
	string jsonName;

	int hp;
	int maxHp;
	int attack;
	int defense;
	float attackDelay;

	int simpleBullet; // ÆÕÍ¨¹¥»÷×Óµ¯id
};