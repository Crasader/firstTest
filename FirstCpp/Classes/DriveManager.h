//-----------------------------------------------------------------------------------------------------------------------------
// ����: �豸����������
// ����: lvxiangsong
// ����: 2013-10-8
// ����: �����豸����
// �汾: 
//
// �޸���           ����	           ����		
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