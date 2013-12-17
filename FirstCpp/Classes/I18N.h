//-----------------------------------------------------------------------------------------------------------------------------
// ����: ���ʻ�������
// ����: lvxiangsong
// ����: 2013-10-8
// ����: ���ʻ�������
// �汾: 
//
// �޸���           ����	           ����		
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
	// ͨ�����ֻ�ȡ�ַ���
	string getString(const char* name) const;
	// ͨ�����ֻ�ȡ�ַ�����֧��int��float��char�ʹ���
	string getStringArgs(const char* name, ...) const;
private:
	CCDictionary* mDictionary;
	static const int I18N_MAX = 1024;
};