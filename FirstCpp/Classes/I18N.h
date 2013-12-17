//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 国际化管理器
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 国际化管理器
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "cocos2d.h"
#include <string>

using namespace std;
USING_NS_CC;

class I18N
{
public:
	I18N(void);
	~I18N(void);
public:
	static I18N* sharedI18N(void);
	static void pure(void);
public:
	// 通过名字获取字符串
	string getString(const char* name) const;
	// 通过名字获取字符串，支持int、float、char型传参
	string getStringArgs(const char* name, ...) const;
private:
	CCDictionary* mDictionary;
	static const int I18N_MAX = 1024;
};