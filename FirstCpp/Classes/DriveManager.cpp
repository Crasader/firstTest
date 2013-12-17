#include "DriveManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include"platform/android/jni/JniHelper.h"
#endif


static DriveManager* mDriveManager = NULL;

DriveManager::DriveManager(void)
{

}

DriveManager::~DriveManager(void)
{
	CC_SAFE_DELETE(mDriveManager);
}

DriveManager* DriveManager::sharedDriveManager()
{
	if (mDriveManager == NULL)
	{
		mDriveManager = new DriveManager();
	}
	return mDriveManager;
}

void DriveManager::pure()
{
	CC_SAFE_DELETE(mDriveManager);
}

void DriveManager::showTestDialog()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/the9/first/DriveHandler","viewDialog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave)
	{
		jstring title = minfo.env->NewStringUTF(I18N::sharedI18N()->getStringArgs("chinese", "wsf").c_str());
		jstring msg = minfo.env->NewStringUTF("提示内容");
		jstring btnlabel = minfo.env->NewStringUTF("确定");
		//jstring args[] = {title, msg, btnlabel};
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,title,msg,btnlabel);
	}
#endif
}