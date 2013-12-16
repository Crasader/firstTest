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
	string getString(const char* str) const;
	//string getString(const char* str, ...) const;
	const char* getCharArray(const char* str) const;
private:
	CCDictionary* mDictionary;
};