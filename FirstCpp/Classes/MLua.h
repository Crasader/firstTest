//-----------------------------------------------------------------------------------------------------------------------------
//                `-.   \    .-'
//        ,-"`````""-\__ |  /							�ļ����ƣ�MLua
//         '-.._    _.-'` '-o,							�ļ�������Lua��װ��ע�����  
//             _>--:{{<   ) |)							�ļ���д��Lumy
//         .-''      '-.__.-o`							�������ڣ�2005.7.1
//        '-._____..-/`  |  \							�������ڣ�2009.6.2
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
	//��������������
	MLua(void);
	virtual ~MLua();
public:
	//��ʼ�����ͷ�
	int Instance(void);
	void Release(void);
public:
	//ע�ắ��
	bool RegisterFunction(const char * szFuncName,lua_CFunction lpFunc);
public:
	//ִ�нű��ļ�
	bool LoadLuaFile(const string & strFileName);
	//ִ�нű��ַ���
	bool LoadLuaString(const string & strString);
public:
	//ִ��һ������
	//ע�⣺szSigΪ�������ͺͷ��ؽ������
	//i��ʾint,d��ʾdouble,s��ʾ�ַ���,p��ʾָ��,uΪ���󣨲���float���ͣ���Ϊ����1.0Ĭ���ǰ���double����ģ�
	//>��ʾ�����ӵ��Ƿ���ֵ���纯����������������һ����int���ͣ��ڶ�����char *���ͣ�����ֵ��int���ͣ���ʾΪ"is>i"
	//ע�⣺����ֵ��ָ�뷽ʽ���룬int a,double b,char * c; ����ExecFunction(....,&a,&b,&c);
	bool ExecFunction(const char * szFuncName,const char * szSig,...);
public:
	//��ȡLUA�ű��е�ȫ�ֱ���
	double Global_To_Double(const char * szName);
	int Global_To_Int(const char * szName);
	string Global_To_String(const char * szName);
public:
	//��ȡLUA״̬
	lua_State * GetLuaState(void);
public:
	//LUA��������
	static int LuaErrorFunction(lua_State * lpLua);
protected:
	int executeFunction(int numArgs);
};
//-----------------------------------------------------------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------------------------------------------------------