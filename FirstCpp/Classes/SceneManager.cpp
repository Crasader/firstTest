#include "SceneManager.h"

// singleton
static SceneManager* mSceneManager = NULL;

SceneManager::SceneManager(void)
{

}

SceneManager::~SceneManager(void)
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVNET_SCENE_VIEW_WAR);
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

void SceneManager::pure()
{
	CC_SAFE_DELETE(mSceneManager);
}

// ����ս������
void SceneManager::viewToWar(CCObject* obj)
{
	CCDirector::sharedDirector()->replaceScene(WarScene::scene());
}