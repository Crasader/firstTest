//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 工具类
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 工具类
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
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

	CCMenuItemImage* createCCMenuItemImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector); // 创建图片按钮
};