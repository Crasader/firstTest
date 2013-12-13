//-----------------------------------------------------------------------------------------------------------------------------
//                `-.   \    .-'
//        ,-"`````""-\__ |  /							文件名称：MLua
//         '-.._    _.-'` '-o,							文件描述：Lua包装，注册对象  
//             _>--:{{<   ) |)							文件编写：Lumy
//         .-''      '-.__.-o`							创建日期：2005.7.1
//        '-._____..-/`  |  \							更新日期：2009.6.2
//                ,-'   /    `-.
//-----------------------------------------------------------------------------------------------------------------------------
#ifndef __MBaseLibrary_MLua_H__
#define __MBaseLibrary_MLua_H__
//-----------------------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" 
{
#endif
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "tolua++.h"
#ifdef __cplusplus
};
#endif
//#include "BaseUnit/MStdString.h"
#include <string>
#include "cocos2d.h"
//#include <assert.h>

USING_NS_CC;
using namespace std;
//-----------------------------------------------------------------------------------------------------------------------------
class MLua
{
protected:
	lua_State					*	m_lpLuaState;
public:
	//构造与析构函数
	MLua(void);
	virtual ~MLua();
public:
	//初始化与释放
	int Instance(void);
	void Release(void);
public:
	//注册函数
	bool RegisterFunction(const char * szFuncName,lua_CFunction lpFunc);
public:
	//执行脚本文件
	bool LoadLuaFile(const string & strFileName);
	//执行脚本字符串
	bool LoadLuaString(const string & strString);
public:
	//执行一个函数
	//注意：szSig为参数类型和返回结果描述
	//i表示int,d表示double,s表示字符串,p表示指针,u为对象（不含float类型，因为常数1.0默认是按照double处理的）
	//>表示后续接的是返回值，如函数有两个参数，第一个是int类型，第二个是char *类型，返回值是int类型，表示为"is>i"
	//注意：返回值用指针方式进入，int a,double b,char * c; 调用ExecFunction(....,&a,&b,&c);
	bool ExecFunction(const char * szFuncName,const char * szSig,...);
public:
	//获取LUA脚本中的全局变量
	double Global_To_Double(const char * szName);
	int Global_To_Int(const char * szName);
	string Global_To_String(const char * szName);
public:
	//获取LUA状态
	lua_State * GetLuaState(void);
public:
	//LUA错误处理函数
	static int LuaErrorFunction(lua_State * lpLua);
protected:
	int executeFunction(int numArgs);
};
//-----------------------------------------------------------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------------------------------------------------------