#include "SceneManager.h"

// singleton
static SceneManager* mSceneManager = NULL;

SceneManager::SceneManager(void)
{

}

SceneManager::~SceneManager(void)
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVNET_SCENE_VIEW_WAR);
	CC_SAFE_DELETE(mSceneManager);
}

SceneManager* SceneManager::shardSceneManager()
{
	if (mSceneManager == NULL)
	{
		mSceneManager = new SceneManager();
		mSceneManager->init();
	}
	return mSceneManager;
}

bool SceneManager::init()
{
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneManager::viewToWar), EVNET_SCENE_VIEW_WAR, NULL);// ����ս������
	return true;
}

// ����ս������
void SceneManager::viewToWar(CCObject* obj)
{
	CCDirector::sharedDirector()->replaceScene(WarScene::scene());
}