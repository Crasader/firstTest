//-----------------------------------------------------------------------------------------------------------------------------
#include "MLua.h"
//-----------------------------------------------------------------------------------------------------------------------------
MLua::MLua(void)
{
	m_lpLuaState = NULL;
}
//.............................................................................................................................
MLua::~MLua()
{
	Release();
}
//.............................................................................................................................
int MLua::Instance(void)
{
	Release();

	try
	{
		m_lpLuaState = lua_open();
		lua_atpanic(m_lpLuaState,LuaErrorFunction);

		luaopen_base(m_lpLuaState);
		luaopen_table(m_lpLuaState);
		//luaopen_io(m_lpLuaState);//为什么会出错，程序退出???
		luaopen_string(m_lpLuaState);
		luaopen_math(m_lpLuaState);

		return(1);
	}
	catch(...)
	{
		//return(ERR_PUBLIC_CANTDO);
		return 0;
	}
}
//.............................................................................................................................
void MLua::Release(void)
{
	try
	{
		if ( m_lpLuaState != NULL )
		{
			lua_close(m_lpLuaState);
			m_lpLuaState = NULL;
		}
	}
	catch(...)
	{

	}
}
//.............................................................................................................................
bool MLua::RegisterFunction(const char * szFuncName,lua_CFunction lpFunc)
{
	try
	{
		lua_pushcfunction(m_lpLuaState,lpFunc);
		lua_setglobal(m_lpLuaState,szFuncName);

		return(true);
	}
	catch(...)
	{
		return(false);
	}
}
//.............................................................................................................................
bool MLua::LoadLuaFile(const string & strFileName)
{
	
	try
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		std::string code("require \"");
		code.append(strFileName);
		code.append("\"");
		luaL_loadfile(m_lpLuaState, code.c_str());
		int result = executeFunction(0);
		return result == 0 ? false : true;
#else
		std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(strFileName.c_str());
		if ( luaL_dofile(m_lpLuaState,fullPath.c_str()) == 0 )
		{
			return(true);
		}
		else
		{
			return(false);
		}
#endif
	}
	catch(...)
	{
		return(false);
	}
}
//.............................................................................................................................
bool MLua::LoadLuaString(const string & strString)
{
	try
	{
		if ( luaL_dostring(m_lpLuaState,strString.c_str()) == 0 )
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
	catch(...)
	{
		return(false);
	}
}
//.............................................................................................................................
bool MLua::ExecFunction(const char * szFuncName,const char * szSig,...)
{
	va_list						stmarker;
	int							argcount = 0;
	int							retcount = 0;
	int							offset;
	char					*	tempptr = (char *)szSig;
	int							tempint;

	try
	{
		va_start(stmarker,szSig);

		lua_settop(m_lpLuaState,0);
		lua_getglobal(m_lpLuaState,szFuncName);

		while ( * tempptr != 0 )
		{
			if ( * tempptr == 'd' )
			{
				lua_pushnumber(m_lpLuaState,va_arg(stmarker,double));
			}
			else if ( * tempptr == 'i' )
			{
				lua_pushnumber(m_lpLuaState,va_arg(stmarker,int));
			}
			else if ( * tempptr == 's' )
			{
				lua_pushstring(m_lpLuaState,va_arg(stmarker,char *));
			}
			else if ( * tempptr == 'p' )
			{
				tempint = (int)va_arg(stmarker,void *);
				lua_pushnumber(m_lpLuaState,tempint);
			}
			else if ( * tempptr == '>' )
			{
				tempptr ++;
				break;
			}
			else
			{
				//无效的参数类型描述
				return(false);
			}

			tempptr ++;
			argcount ++;
		}

		retcount = tempptr == NULL ? 0 : strlen(tempptr);
		if ( lua_pcall(m_lpLuaState,argcount,retcount,0) != 0 )
		{
			//执行函数失败
			return(false);
		}

		offset = - retcount;
		while ( * tempptr )
		{
			switch ( * tempptr ++ )
			{
			case 'd':
				if ( lua_isnumber(m_lpLuaState,offset) == 0 )
				{
					//返回类型与描述类型不匹配
					return(false);
				}
				* va_arg(stmarker,double *) = lua_tonumber(m_lpLuaState,offset);
				break;
			case 'i':
				if ( lua_isnumber(m_lpLuaState,offset) == 0 )
				{
					//返回类型与描述类型不匹配
					return(false);
				}
				* va_arg(stmarker,int *) = (int)lua_tonumber(m_lpLuaState,offset);
				break;
			case 's':
				if ( lua_isstring(m_lpLuaState,offset) == 0 )
				{
					//返回类型与描述类型不匹配
					return(false);
				}
				* va_arg(stmarker,char **) = (char *)lua_tostring(m_lpLuaState,offset);
				break;
			default:
				//无效的参数类型描述
				return(false);
			};

			offset ++;
		};

		va_end(stmarker);

		return(true);
	}
	catch(...)
	{
		return(false);
	}
}
//.............................................................................................................................
lua_State * MLua::GetLuaState(void)
{
	return(m_lpLuaState);
}
//.............................................................................................................................
double MLua::Global_To_Double(const char * szName)
{
	double					temp;

	try
	{
		lua_settop(m_lpLuaState,0);
		lua_getglobal(m_lpLuaState,szName);
		//assert(lua_isnumber(m_lpLuaState,-1) != 0);
		temp = lua_tonumber(m_lpLuaState,-1);

		return(temp);
	}
	catch(...)
	{
		return(0.0);
	}
}
//.............................................................................................................................
int MLua::Global_To_Int(const char * szName)
{
	int					temp;

	try
	{
		lua_settop(m_lpLuaState,0);
		lua_getglobal(m_lpLuaState,szName);
		//assert(lua_isnumber(m_lpLuaState,-1) != 0);
		temp = (int)lua_tonumber(m_lpLuaState,-1);

		return(temp);
	}
	catch(...)
	{
		return(0);
	}
}
//.............................................................................................................................
string MLua::Global_To_String(const char * szName)
{
	string					temp;

	try
	{
		lua_settop(m_lpLuaState,0);
		lua_getglobal(m_lpLuaState,szName);
		//assert(lua_isstring(m_lpLuaState,-1) != 0);
		temp = lua_tostring(m_lpLuaState,-1);

		return(temp);
	}
	catch(...)
	{
		return("lua error");
	}
}
//.............................................................................................................................
//.............................................................................................................................
//.............................................................................................................................
//.............................................................................................................................
int MLua::LuaErrorFunction(lua_State * lpLua)
{
	char					tempbuf[256];

	//cs_strncpy(tempbuf,lua_tostring(lpLua,1),sizeof(tempbuf));
	const char* szSource = lua_tostring(lpLua,1);
	int iSize = sizeof(tempbuf);
	if (tempbuf != NULL && szSource != NULL && iSize > 0)
	{
		strncat(tempbuf,szSource,iSize);
		tempbuf[iSize - 1] = 0;
	}
	//assert(0);
	throw "lua error";
	return(1);
}
//-----------------------------------------------------------------------------------------------------------------------------
int MLua::executeFunction(int numArgs)
{
	int functionIndex = -(numArgs + 1);
	if (!lua_isfunction(m_lpLuaState, functionIndex))
	{
		CCLOG("value at stack [%d] is not function", functionIndex);
		lua_pop(m_lpLuaState, numArgs + 1); // remove function and arguments
		return 0;
	}

	int traceback = 0;
	lua_getglobal(m_lpLuaState, "__G__TRACKBACK__");                         /* L: ... func arg1 arg2 ... G */
	if (!lua_isfunction(m_lpLuaState, -1))
	{
		lua_pop(m_lpLuaState, 1);                                            /* L: ... func arg1 arg2 ... */
	}
	else
	{
		lua_insert(m_lpLuaState, functionIndex - 1);                         /* L: ... G func arg1 arg2 ... */
		traceback = functionIndex - 1;
	}

	int error = 0;
	//++m_callFromLua;
	error = lua_pcall(m_lpLuaState, numArgs, 1, traceback);                  /* L: ... [G] ret */
	//--m_callFromLua;
	if (error)
	{
		if (traceback == 0)
		{
			CCLOG("[LUA ERROR] %s", lua_tostring(m_lpLuaState, - 1));        /* L: ... error */
			lua_pop(m_lpLuaState, 1); // remove error message from stack
		}
		else                                                            /* L: ... G error */
		{
			lua_pop(m_lpLuaState, 2); // remove __G__TRACKBACK__ and error message from stack
		}
		return 0;
	}

	// get return value
	int ret = 0;
	if (lua_isnumber(m_lpLuaState, -1))
	{
		ret = lua_tointeger(m_lpLuaState, -1);
	}
	else if (lua_isboolean(m_lpLuaState, -1))
	{
		ret = lua_toboolean(m_lpLuaState, -1);
	}
	// remove return value from stack
	lua_pop(m_lpLuaState, 1);                                                /* L: ... [G] */

	if (traceback)
	{
		lua_pop(m_lpLuaState, 1); // remove __G__TRACKBACK__ from stack      /* L: ... */
	}

	return ret;
}