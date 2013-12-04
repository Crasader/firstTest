#include "LoadScene.h"

LoadScene::LoadScene():mLayer(NULL)
{

}

LoadScene::~LoadScene()
{
	if (mLayer)
	{
		mLayer->unscheduleUpdate();
		mLayer->removeAllChildrenWithCleanup(true);
		mLayer->removeFromParentAndCleanup(true);
		mLayer = NULL;
	}
	this->removeAllChildrenWithCleanup(true);
}

CCScene* LoadScene::scene()
{
	CCScene* mScene = CCScene::create();
	LoadScene* mLoadScene = LoadScene::create();

	mScene->addChild(mLoadScene);

	return mScene;
}

bool LoadScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//创建一个UILayer层
	mLayer = UILayer::create();
	//开启刷新函数
	mLayer->scheduleUpdate();
	//将UILayer层加入到当前的场景
	this->addChild(mLayer);
	//使用json文件给Layer层添加CocoStudio生成的控件
	mUi = CCUIHELPER->createWidgetFromJsonFile("LoadUI/LoadUI_1.json");
	mLayer->addWidget(mUi);
	//UILoadingBar* bar = (UILoadingBar*)mUi->getChildByName("LoadingBar01");
	//bar->setTexture("a.png");
	//UILoadingBar* bar = (UILoadingBar*)mUi->getChildByName("LoadingBar01");
	//UIImageView* img = (UIImageView*)mUi->getChildByName("ImageView");
	//img->loadTexture("a.png");

	//UILayer* lay = UILayer::create();
	//UILoadingBar* bar1 = UILoadingBar::create();
	//bar1->copyWithZone((CCZone*)bar);
	//lay->addWidget(bar1);
	//layer->addChild(lay);

	return true;
}

void LoadScene::setProgress(float value)
{
	int result = int(value * 100);
	UILoadingBar* bar = (UILoadingBar*)mUi->getChildByName("LoadingBar01");
	bar->setPercent(result);

	UILabel* lab = (UILabel*)mUi->getChildByName("ProgresstLabel");
	char src[10];
	sprintf(src, "%d%%", result);
	lab->setText(src);
}