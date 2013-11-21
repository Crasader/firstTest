#pragma once

#include <string>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class SkillVo : public CCObject
{
public:
	SkillVo();
	~SkillVo();
	bool init();
	CREATE_FUNC(SkillVo);

	float getMaxCd() const;
	float getCurrentCd() const;
	float getPercent() const;

	void setMaxCd(float value);
	void setCurrentCd(float value);
	void setPercent(float value);

private:
	float mMaxCd;
	float mCurrentCd;
};