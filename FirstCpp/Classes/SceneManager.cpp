#include "SceneManager.h"

// singleton
static SceneManager* mSceneManager = NULL;

SceneManager::SceneManager(void)
{

}

SceneManager::~SceneManager(void)
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_SCENE_VIEW_MAIN);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_SCENE_VIEW_WAR);
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
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneManager::viewToMain), EVENT_SCENE_VIEW_MAIN, NULL);// ����������
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneManager::viewToWar), EVENT_SCENE_VIEW_WAR, NULL);// ����ս������
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

// ����������
void SceneManager::viewToMain(CCObject* obj)
{
	CCDirector::sharedDirector()->replaceScene(GameWorld::scene());
}