#include "LoadScene.h"

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

	//����һ��UILayer��
	UILayer* layer = UILayer::create();
	//����ˢ�º���
	layer->scheduleUpdate();
	//��UILayer����뵽��ǰ�ĳ���
	this->addChild(layer);
	//ʹ��json�ļ���Layer�����CocoStudio���ɵĿؼ�
	mUi = CCUIHELPER->createWidgetFromJsonFile("LoadUI/LoadUI_1.json");
	layer->addWidget(mUi);

	//UILoadingBar* bar = (UILoadingBar*)mUi->getChildByName("LoadingBar01");

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