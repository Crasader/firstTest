#include "PersonVo.h"

PersonVo::PersonVo(void):hp(1000), attack(100), attackDelay(2.0f), defense(40), maxHp(1000)
{
	skillArr = CCArray::create();
	CC_SAFE_RETAIN(skillArr);
}

PersonVo::~PersonVo(void)
{
	CC_SAFE_RELEASE_NULL(skillArr);
}

bool PersonVo::init()
{
	return true;
}

CCArray* PersonVo::getSkillArr() const
{
	return skillArr;
}