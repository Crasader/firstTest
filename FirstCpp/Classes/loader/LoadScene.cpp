#include "LoadScene.h"

LoadScene::LoadScene():mLayer(NULL)
{

}

LoadScene::~LoadScene()
{
	this->removeAllChildrenWithCleanup(true);
	mLayer = NULL;
}

CCScene* LoadScene::scene()
{
	CCScene* mScene = CCScene::create();
	LoadScene* mLoadScene = LoadScene::create();

	mScene->addChild(mLoadScene);

	return mScene;
}

void LoadScene::onExit()
{
	if (mLayer)
	{
		mLayer->removeWidgetAndCleanUp(mUi, true);
		mLayer->unscheduleUpdate();
		mLayer->removeAllChildrenWithCleanup(true);
	}
	BaseLayer::onExit();
}

bool LoadScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	//return true;
	mLayer = UILayer::create();
	mLayer->scheduleUpdate();
	this->addChild(mLayer);
	mUi = GUIReader::shareReader()->widgetFromJsonFile("LoadUI/LoadUI_1.json");
	mLayer->addWidget(mUi);
	return true;
}

void LoadScene::setProgress(float value)
{
	//return;
	int result = int(value * 100);
	UILoadingBar* bar = (UILoadingBar*)mUi->getChildByName("LoadingBar01");
	bar->setPercent(result);

	UILabel* lab = (UILabel*)mUi->getChildByName("ProgresstLabel");
	char src[10];
	sprintf(src, "%d%%", result);
	lab->setText(src);
}