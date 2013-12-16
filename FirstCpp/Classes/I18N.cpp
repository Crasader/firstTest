#include "I18N.h"

static I18N* mShredI18N = NULL;

I18N::I18N(void):mDictionary(NULL)
{
	mDictionary = CCDictionary::createWithContentsOfFile("i18n_cn.xml");
	CC_SAFE_RETAIN(mDictionary);
}

I18N::~I18N(void)
{
	CC_SAFE_RELEASE_NULL(mDictionary);
	CC_SAFE_DELETE(mShredI18N);
}

I18N* I18N::sharedI18N()
{
	if (mShredI18N == NULL)
	{
		mShredI18N = new I18N();
	}
	return mShredI18N;
}

void I18N::pure()
{
	CC_SAFE_DELETE(mShredI18N);
}

string I18N::getString(const char* str) const
{
	const CCString* ccstr = mDictionary->valueForKey(str);
	return ccstr->m_sString;
}

//string I18N::getString(const char* str, ...) const
//{
//	
//}

const char* I18N::getCharArray(const char* str) const
{
	return getString(str).c_str();
}