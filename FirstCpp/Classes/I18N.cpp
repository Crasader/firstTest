#include "I18N.h"
#include "CCStdC.h"

static I18N* mShredI18N = NULL;

//-----------------------------------------------------------------------------------------------------------------------------
I18N::I18N(void):mDictionary(NULL)
{
	mDictionary = CCDictionary::createWithContentsOfFile("i18n_cn.xml");
	CC_SAFE_RETAIN(mDictionary);
}

//-----------------------------------------------------------------------------------------------------------------------------
I18N::~I18N(void)
{
	CC_SAFE_RELEASE_NULL(mDictionary);
}

//-----------------------------------------------------------------------------------------------------------------------------
I18N* I18N::sharedI18N()
{
	if (mShredI18N == NULL)
	{
		mShredI18N = new I18N();
	}
	return mShredI18N;
}

//-----------------------------------------------------------------------------------------------------------------------------
void I18N::pure()
{
	CC_SAFE_DELETE(mShredI18N);
}

//-----------------------------------------------------------------------------------------------------------------------------
// 通过名字获取字符串
string I18N::getString(const char* name) const
{
	const CCString* ccstr = mDictionary->valueForKey(name);
	return ccstr->m_sString;
}

//-----------------------------------------------------------------------------------------------------------------------------
// 通过名字获取字符串，支持int、float、char型传参
string I18N::getStringArgs(const char* name, ...) const
{
	const CCString* ccstr = mDictionary->valueForKey(name);
	char szBuf[I18N_MAX];
	va_list ap;
	va_start(ap, name);
	vsnprintf(szBuf, I18N_MAX, ccstr->m_sString.c_str(), ap);
	va_end(ap);
	return string(szBuf);
}