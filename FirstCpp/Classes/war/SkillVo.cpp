#include "SkillVo.h"

SkillVo::SkillVo():mMaxCd(10), mCurrentCd(4)
{

}

SkillVo::~SkillVo()
{

}

bool SkillVo::init()
{
	return true;
}

float SkillVo::getMaxCd() const
{
	return mMaxCd;
}
float SkillVo::getCurrentCd() const
{
	return mCurrentCd;
}
float SkillVo::getPercent() const
{
	if (mMaxCd <= 0) 
		return 100;
	else
		return int((1 - (mCurrentCd / mMaxCd)) * 100);
}

void SkillVo::setMaxCd(float value)
{
	mMaxCd = value;
}
void SkillVo::setCurrentCd(float value)
{
	if (value < 0) 
		value = 0;
	mCurrentCd = value;
}
void SkillVo::setPercent(float value)
{
	if (mMaxCd <= 0)
		mCurrentCd = 0;
	else
		mCurrentCd = (1 - value / 100) * mMaxCd;
}