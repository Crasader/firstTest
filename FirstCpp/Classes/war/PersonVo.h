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

	string name;
	int posId;
	int gender;
	string pngName;
	string xmlName;
	string jsonName;

	float hp;
	float attack;
	float defense;
	float attackDelay;

	int simpleBullet; // ÆÕÍ¨¹¥»÷×Óµ¯id
};