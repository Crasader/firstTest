#include "PersonVo.h"

PersonVo::PersonVo(void):hp(1000), attack(100), attackDelay(2.0f), defense(40), maxHp(1000)
{

}

PersonVo::~PersonVo(void)
{

}

bool PersonVo::init()
{
	return true;
}