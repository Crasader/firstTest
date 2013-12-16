//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 设备驱动管理器
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 调用设备功能
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "cocos2d.h"
#include <string>
#include "I18N.h"

using namespace std;
USING_NS_CC;

class DriveManager
{
public:
	DriveManager(void);
	virtual ~DriveManager(void);
public:
	static DriveManager* sharedDriveManager();
	static void pure();
public:
	void showTestDialog(void);
};