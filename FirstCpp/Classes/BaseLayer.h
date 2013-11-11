#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BaseLayer : public cocos2d::CCLayer
{
public:
	BaseLayer();
	~BaseLayer();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	virtual void keyBackClicked();//¼àÌýAndroid ·µ»Ø¼ü
	virtual void keyMenuClicked();//¼àÌýAndroid ²Ëµ¥¼ü
#endif
};