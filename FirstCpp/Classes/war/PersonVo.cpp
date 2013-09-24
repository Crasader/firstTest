#include "PersonVo.h"

PersonVo::PersonVo(void):hp(1000.0f), attack(100.0f), attackDelay(2.0f), defense(40.0f)
{

}

PersonVo::~PersonVo(void)
{

}

bool PersonVo::init()
{
	return true;
}