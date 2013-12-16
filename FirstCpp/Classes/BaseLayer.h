//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 场景基类
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 场景基类
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "cocos2d.h"

USING_NS_CC;

class BaseLayer : public cocos2d::CCLayer
{
public:
	BaseLayer();
	~BaseLayer();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	virtual void keyBackClicked();//监听Android 返回键
	virtual void keyMenuClicked();//监听Android 菜单键
#endif
};