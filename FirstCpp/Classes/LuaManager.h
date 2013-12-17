//-----------------------------------------------------------------------------------------------------------------------------
// ����: lua������
// ����: lvxiangsong
// ����: 2013-10-8
// ����: lua������
// �汾: 
//
// �޸���           ����	           ����		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "MLua.h"
#include "cocos2d.h"
#include "EnumCommon.h"

USING_NS_CC;

class LuaManager
{
public:
	LuaManager(void);
	virtual ~LuaManager();
public:
	static LuaManager* shareLuaManager();
	static void pure();
	MLua* getMLua(void);
public:
	static int Max(int a,int b);
	static int MaxLua(lua_State * L);
	static int SetFormation(lua_State * L);
private:
	MLua* mMlua;

public:
	int aTeam[9];
	int bTeam[9];
};