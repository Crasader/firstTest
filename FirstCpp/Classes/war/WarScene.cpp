#include "WarScene.h"
#include "cocos-ext.h"
#include "PartenerView.h"
#include "SimpleControll.h"
#include "WarModel.h"
#include "EnumCommon.h"
#include "ConfigManager.h"

using namespace cocos2d::extension;
USING_NS_CC;

WarScene::WarScene(void)
{
}


WarScene::~WarScene(void)
{
}

CCScene* WarScene::scene()
{
	CCScene* mScene = CCScene::create();
	WarScene* mWarScene = WarScene::create();

	mScene->addChild(mWarScene);

	return mScene;
}

bool WarScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//mSTimer = CCTimer::initWithTarget(this, SEL_SCHEDULE(WarScene::onTimerHandler()));
	schedule(schedule_selector(WarScene::onTimerHandler), 0.5f);

	//bg = CCSprite::create("bg.jpg");
	//bg->setAnchorPoint(ccp(0, 0));
	//bg->setPosition(ccp(0, 0));
	//addChild(bg);
	UILayer* tlayer = UILayer::create();
	addChild(tlayer);
	UIWidget* root = CCUIHELPER->createWidgetFromJsonFile("WarUI_1.json");
	tlayer->addWidget(root);
	 
	//CCNode* pNode = CCSSceneReader::sharedSceneReader()->createNodeWithSceneFile("WarScene.json");
	//addChild(pNode);
	//CCNode* root = pNode->getChildByTag(10011);

	//bg1 = CCSprite::create("background.png");
	//bg2 = CCSprite::create("background.png");
	//bg1->setRotation(90);
	//bg1->setAnchorPoint(ccp(0, 0));
	//bg1->setPosition(ccp(0, visibleSize.height));
	//bg2->setRotation(90);
	//bg2->setAnchorPoint(ccp(0, 0));
	//bg2->setPosition(ccp(1020, visibleSize.height));
	//addChild(bg1);
	//addChild(bg2);

	CCLabelTTF* pLabel = CCLabelTTF::create("", "Arial", 24);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height - pLabel->getContentSize().height - 100));

	// add the label as a child to this layer
	addChild(pLabel, 1);

	SimpleControll* movecontroll = SimpleControll::create();
	movecontroll->setSpeed(3);

	hero = PartenerView::create();
	hero->setBaseId(3);
	hero->setPosition(ccp(visibleSize.width / 4, visibleSize.height / 4));
	addChild(hero, 2);

	hero->setController(movecontroll);

	CCDictionary* strings = CCDictionary::createWithContentsOfFile("i18n_cn.xml");
	const char* str = ((CCString*)strings->objectForKey("japanese"))->m_sString.c_str();
	pLabel->setString(str);
	movecontroll = SimpleControll::create();
	movecontroll->setSpeed(2);
	stone = PartenerView::create();
	stone->setBaseId(1);
	stone->setPosition(ccp(visibleSize.width / 2 + 200, visibleSize.height / 2));
	stone->setTarget(hero);
	stone->setController(movecontroll);
	addChild(stone);

	CCArray* partener = WarModel::shardWarModel()->getPartenerArray();
	CCArray* enemy = WarModel::shardWarModel()->getEnemyArray();

	for (int i = partener->count() - 1; i >= 0; i--) 
	{
		PartenerView* pObj = (PartenerView*)partener->objectAtIndex(i);
		pObj->setBaseId(1);
		char* posid = new char[12];
		sprintf(posid, "left%d", i);
		CCPoint tp = root->getChildByName("ImageView")->getChildByName(posid)->getPosition();
		pObj->setPosition(tp);
		delete posid;

		movecontroll = SimpleControll::create();
		movecontroll->setSpeed(0.5 + i * 0.5);
		pObj->setController(movecontroll);
		if (enemy->count() > i) pObj->setTarget((PartenerView*)enemy->objectAtIndex(i));

		addChild(pObj);
	}
	
	for (int i = enemy->count() - 1; i >= 0; i--) 
	{
		PartenerView* pObj = (PartenerView*)enemy->objectAtIndex(i);
		pObj->setBaseId(1);
		char* posid = new char[12];
		sprintf(posid, "right%d", i);
		CCPoint tp = root->getChildByName("ImageView")->getChildByName(posid)->getPosition();
		pObj->setPosition(tp);
		delete posid;

		movecontroll = SimpleControll::create();
		movecontroll->setSpeed(0.5 + i * 0.5);
		pObj->setController(movecontroll);
		pObj->setTarget((PartenerView*)partener->objectAtIndex(i));

		addChild(pObj);
	}

	//CCEGLView* eglView = CCEGLView::sharedOpenGLView();
	//eglView->setFrameSize(960, 640);
	//eglView->setWndProc(myWndProcHook);
	
	scheduleUpdate();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
	return true;

}

//LRESULT myWndProcHook(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed)
//{
//	switch (message)
//	{
//	case WM_KEYDOWN:
//	case WM_KEYUP:
//		{
//			//以FrameSize == DesignResolutionSize时的坐标设定
//			CCPoint pt = CCPointZero;
//			switch (wParam)
//			{
//			case 'A':   //向左
//				{
//					pt = ccp(25, 255);
//				}
//				break;
//			case 'D':   //向右
//				{
//					pt = ccp(95, 256);
//				}
//				break;
//			case 'W':   //向上
//				{
//					pt = ccp(63, 214);
//				}
//				break;
//			case 'S':   //向下
//				{
//					pt = ccp(62, 290);
//				}
//				break;
//			case 'J':   //攻击
//				{
//					pt = ccp(367, 277);
//				}
//				break;
//			case 'K':   //跳跃
//				{
//					pt = ccp(445, 247);
//				}
//				break;
//			default:
//				return 0;
//			}
//		}
//	}
//
//	return 0;
//}

// 每帧执行
void WarScene::update(float delta)
{
	//bg1->setPosition(ccp(bg1->getPosition().x - 3, bg1->getPosition().y));
	//bg2->setPosition(ccp(bg2->getPosition().x - 3, bg2->getPosition().y));

	//if (bg1->getPosition().x < -1020)
	//{
	//	bg1->setPosition(ccp(1020, 640));
	//}
	//if (bg2->getPosition().x < -1020)
	//{
	//	bg2->setPosition(ccp(1020, 640)); 
	//}
}

// 该函数每秒钟执行一次
void WarScene::onTimerHandler(float dt)
{
	CCArray* partener = WarModel::shardWarModel()->getPartenerArray();
	for (int i = partener->count() - 1; i >= 0; i--) 
	{
		PartenerView* pObj = (PartenerView*)partener->objectAtIndex(i);
		pObj->getController()->checkTargetPos();
	}

	CCArray* enemy = WarModel::shardWarModel()->getEnemyArray();
	for (int i = enemy->count() - 1; i >= 0; i--) 
	{
		PartenerView* pObj = (PartenerView*)enemy->objectAtIndex(i);
		pObj->getController()->checkTargetPos();
	}

	if (stone != NULL)
	{ 
		if (stone->getTarget() == NULL)
		{
			//for (int i = partener->count() - 1; i >= 0; i--) 
			//{
			if (partener->count() > 0) stone->setTarget((PartenerView*)partener->objectAtIndex(0));
			//}
		}
		stone->getController()->checkTargetPos();
	}

	checkDeep(); // 深度排序
}

// 检查深度排序
void WarScene::checkDeep()
{
	CCArray* partener = WarModel::shardWarModel()->getPartenerArray();
	CCArray* enemy = WarModel::shardWarModel()->getEnemyArray();

	for (int i = partener->count() - 1; i >= 0; i--) 
	{
		PartenerView* pObj = (PartenerView*)partener->objectAtIndex(i);
		this->reorderChild(pObj, 1000 - pObj->getPositionY());
	}

	for (int i = enemy->count() - 1; i >= 0; i--) 
	{
		PartenerView* pObj = (PartenerView*)enemy->objectAtIndex(i);
		this->reorderChild(pObj, 1000 - pObj->getPositionY());
	}

	this->reorderChild(hero, 1000 - hero->getPositionY());
	stone->reorderChild(stone, 1000 - stone->getPositionY());
}

// 触摸开始
bool WarScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->getLocation();
	printf("%f,%f",touchPoint.x,touchPoint.y);
	hero->getController()->moveTo(touchPoint);
	return true;
}

// 触摸移动
void WarScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->getLocation();
	printf("%f,%f",touchPoint.x,touchPoint.y);
}

// 触摸结束
void WarScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->getLocation();
	printf("%f,%f",touchPoint.x,touchPoint.y);
}
