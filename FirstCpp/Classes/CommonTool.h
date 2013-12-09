#pragma once

#include "cocos2d.h"

USING_NS_CC;

class CommonTool
{
public:
	CommonTool();
	~CommonTool();
	static CommonTool* shardCommonTool();
	bool init();
	static void pure();

	CCMenuItemImage* createCCMenuItemImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector); // ´´½¨Í¼Æ¬°´Å¥
};