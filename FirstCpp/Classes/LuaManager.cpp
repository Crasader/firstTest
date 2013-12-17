#include "LuaManager.h"

static LuaManager* mShareManager = NULL;

LuaManager::LuaManager():mMlua(NULL)
{
	mMlua = new MLua();
	mMlua->Instance();
	mMlua->RegisterFunction("mymax", &LuaManager::MaxLua);
	mMlua->RegisterFunction("setFormation", &LuaManager::SetFormation);
}

LuaManager::~LuaManager()
{
	mMlua->Release();
	delete mMlua;
}

LuaManager* LuaManager::shareLuaManager()
{
	if (mShareManager == NULL)
	{
		mShareManager = new LuaManager();
	}
	return mShareManager;
}

void LuaManager::pure()
{
	CC_SAFE_DELETE(mShareManager);
}

MLua* LuaManager::getMLua(void)
{
	return mMlua;
}

int LuaManager::Max(int a,int b)
{
	return(a>b?a:b);
}

int LuaManager::MaxLua(lua_State * L)
{
	int a,b,c;

	a = luaL_checkint(L,1);
	b = luaL_checkint(L,2);

	c = Max(a,b);

	lua_pushinteger(L,c);

	return(1);
}

int LuaManager::SetFormation(lua_State * L)
{
	size_t sizea, sizeb;
	const char* a;
	const char* b;
	a = luaL_checklstring(L, 1, &sizea);
	b = luaL_checklstring(L, 2, &sizeb);
	LuaManager* m = LuaManager::shareLuaManager();
	
	for (size_t i = 0; i < sizea; i++)
	{
		m->aTeam[i] = a[i] - '0';
	}

	for (size_t i = 0; i < sizeb; i++)
	{
		m->bTeam[i] = b[i] - '0';
	}
	return 1;
}
