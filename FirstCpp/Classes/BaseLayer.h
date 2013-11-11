#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BaseLayer : public cocos2d::CCLayer
{
public:
	BaseLayer();
	~BaseLayer();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	virtual void keyBackClicked();//����Android ���ؼ�
	virtual void keyMenuClicked();//����Android �˵���
#endif
};