#include "WarScene.h"
#include "cocos-ext.h"
#include "PartenerView.h"
#include "SimpleControll.h"
#include "WarModel.h"
#include "EnumCommon.h"
#include "ConfigManager.h"
#include "EnumEvent.h"
#include "SkillVo.h"
#include "CommonTool.h"
#include "GameScene.h"

using namespace cocos2d::extension;
USING_NS_CC;

WarScene::WarScene(void):mTouchEntity(NULL)
{
	touchEntityArr = CCArray::create();
	CC_SAFE_RETAIN(touchEntityArr);
	mSkillBtnArr = CCArray::create();
	CC_SAFE_RETAIN(mSkillBtnArr);
}


WarScene::~WarScene(void)
{
	CC_SAFE_RELEASE_NULL(touchEntityArr);
	CC_SAFE_RELEASE_NULL(mSkillBtnArr);
}

void WarScene::onEnter()
{
	CCLayer::onEnter();
	
	
	// 添加侦听事件
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::addTouchedEntity), EVENT_WAR_ADD_TOUCH_ENTITY, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::entityTouchEnd), EVENT_WAR_ADD_TOUCH_END, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::addEffect), EVENT_WAR_ADD_EFFECT, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::onEntityDie), EVENT_WAR_ENTITY_DIE, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::onUseSkill), EVENT_WAR_USE_SKILL, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::addEffect), EVENT_WAR_SHOW_BLOOD_FONT, NULL);

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);

	mTouchX = 0;
	mBeforX = 0;

	mLayerBg = CCNode::create();
	mLayerEntity = CCNode::create();
	mLayerEffect = CCNode::create();
	mLayerUI = CCNode::create();
	mLayerBg->setPosition(CCPointZero);
	mLayerEntity->setPosition(CCPointZero);
	mLayerEffect->setPosition(CCPointZero);
	mLayerUI->setPosition(CCPointZero);
	addChild(mLayerBg, 1);
	addChild(mLayerEntity, 2);
	addChild(mLayerEffect, 3);
	addChild(mLayerUI, 4);


	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//mSTimer = CCTimer::initWithTarget(this, SEL_SCHEDULE(WarScene::onTimerHandler()));
	schedule(schedule_selector(WarScene::onTimerHandler), 0.5f);
	schedule(schedule_selector(WarScene::onSkillTimerHandler), 0.1f);

	UILayer* tlayer = UILayer::create();
	addChild(tlayer, 0);
	UIWidget* root = CCUIHELPER->createWidgetFromJsonFile("WarUI_1.json");
	root->setPosition(origin);
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
	//mLayerBg->addChild(bg1);
	//mLayerBg->addChild(bg2);

	CCLabelTTF* pLabel = CCLabelTTF::create("", "Arial", 24);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height - pLabel->getContentSize().height - 100));

	// add the label as a child to this layer
	mLayerUI->addChild(pLabel);

	SimpleControll* movecontroll = SimpleControll::create();
	//movecontroll->setSpeed(3);

	//hero = PartenerView::create();
	//hero->setBaseId(4);
	//hero->setPosition(ccp(visibleSize.width / 4, visibleSize.height / 4));
	//addEntity(hero);

	//hero->setController(movecontroll);

	CCDictionary* strings = CCDictionary::createWithContentsOfFile("i18n_cn.xml");
	const char* str = ((CCString*)strings->objectForKey("japanese"))->m_sString.c_str();
	pLabel->setString(str);
	movecontroll = SimpleControll::create();
	//movecontroll->setSpeed(2);
	//stone = PartenerView::create();
	//stone->setBaseId(2);
	//stone->setPosition(ccp(visibleSize.width / 2 + 200, visibleSize.height / 2));
	//stone->setTarget(hero);
	//stone->setController(movecontroll);
	//addEntity(stone);

	CCArray* partener = WarModel::shardWarModel()->getPartenerArray();
	CCArray* enemy = WarModel::shardWarModel()->getEnemyArray();

	int tempa[] = {1,1,2,3};
	int tempb[] = {4,5,6,5};
	for (int i = partener->count() - 1; i >= 0; i--) 
	{
		PartenerView* pObj = (PartenerView*)partener->objectAtIndex(i);
		pObj->setBaseId(tempa[i]);
		char* posid = new char[12];
		sprintf(posid, "left%d", pObj->getInfo()->posId);
		CCPoint tp = root->getChildByName("ImageView")->getChildByName(posid)->getPosition();
		pObj->setPosition(tp);
		delete posid;

		movecontroll = SimpleControll::create();
		//movecontroll->setSpeed(0.5 + i * 0.5);
		pObj->setController(movecontroll);
		//if (enemy->count() > i) pObj->setTarget((PartenerView*)enemy->objectAtIndex(i));

		addEntity(pObj);
	}

	for (int i = enemy->count() - 1; i >= 0; i--) 
	{
		PartenerView* pObj = (PartenerView*)enemy->objectAtIndex(i);
		pObj->setBaseId(tempb[i]);
		char* posid = new char[12];
		sprintf(posid, "right%d", pObj->getInfo()->posId);
		CCPoint tp = root->getChildByName("ImageView")->getChildByName(posid)->getPosition();
		pObj->setPosition(tp);
		delete posid;

		movecontroll = SimpleControll::create();
		//movecontroll->setSpeed(0.5 + i * 0.5);
		pObj->setController(movecontroll);
		//pObj->setTarget((PartenerView*)partener->objectAtIndex(i));

		addEntity(pObj);
	}

	initUI();

	scheduleUpdate();
}

void WarScene::onExit()
{
	purgeSelf();
	CCLayer::onExit();
}

CCScene* WarScene::scene()
{
	CCScene* mScene = CCScene::create();
	WarScene* mWarScene = WarScene::create();

	mScene->addChild(mWarScene, 0, 1);

	return mScene;
}

bool WarScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	return true;

}

void WarScene::purgeSelf()
{
	// 移除侦听事件
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_USE_SKILL);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_ENTITY_DIE);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_ADD_EFFECT);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_ADD_TOUCH_END);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_ADD_TOUCH_ENTITY);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_SHOW_BLOOD_FONT);

	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	unschedule(schedule_selector(WarScene::onSkillTimerHandler));
	unschedule(schedule_selector(WarScene::onTimerHandler));
	unscheduleUpdate();

	this->removeAllChildrenWithCleanup(true);
}

void WarScene::initUI()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	for (int i = 0; i < 5; i++)
	{
		SkillBtn* sbtn0 = SkillBtn::create();
		sbtn0->setPosition(ccp(origin.x + 60 + 110*i, origin.y - 60 + visibleSize.height));
		sbtn0->setVisible(false);
		mLayerUI->addChild(sbtn0);
		mSkillBtnArr->addObject(sbtn0);
	}

	// 创建返回按钮
	CCMenuItemImage *pCloseItem = CommonTool::shardCommonTool()->createCCMenuItemImage(
		"war_commonui_back.png",
		"war_commonui_back.png",
		NULL,
		this,
		menu_selector(WarScene::menuCloseCallback));
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width / 2, origin.y + visibleSize.height - pCloseItem->getContentSize().height / 2));
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	mLayerUI->addChild(pMenu);
}

// 返回按钮事件处理
void WarScene::menuCloseCallback(CCObject* pSender)
{
	purgeSelf();
	CCScene *pScene = GameWorld::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
	CCDirector::sharedDirector()->purgeCachedData();
	//CCAnimationCache::purgeSharedAnimationCache();
	//CCSpriteFrameCache::purgeSharedSpriteFrameCache();
	//CCTextureCache::purgeSharedTextureCache();
	//CCShaderCache::purgeSharedShaderCache();
	//CCFileUtils::purgeFileUtils();
}

void WarScene::onSkillTimerHandler(float dt)
{
	CCArray* heros = WarModel::shardWarModel()->getPartenerArray();
	for (int j = heros->count() - 1; j >= 0; j--)
	{
		PersonView* hero = (PersonView*)heros->objectAtIndex(j);
		for (int i = hero->getInfo()->getSkillArr()->count() - 1; i >= 0; i--)
		{
			SkillVo* vo = (SkillVo*)hero->getInfo()->getSkillArr()->objectAtIndex(i);
			vo->setCurrentCd(vo->getCurrentCd() - dt);
			if (mTouchEntity != NULL && mTouchEntity == hero)
			{
				SkillBtn* tbn = (SkillBtn*)mSkillBtnArr->objectAtIndex(i);
				tbn->setId(j*10 + i);
				tbn->setPercent(vo->getPercent());
			}
		}
	}
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
		if (pObj->getTarget() == NULL || WarModel::shardWarModel()->isDie((PersonView*)pObj->getTarget()))
		{
			pObj->setTarget(getTargetBySelfPos(0, pObj->getInfo()->posId));
		}
		pObj->getController()->checkTargetPos();
	}

	CCArray* enemy = WarModel::shardWarModel()->getEnemyArray();
	for (int i = enemy->count() - 1; i >= 0; i--) 
	{
		PartenerView* pObj = (PartenerView*)enemy->objectAtIndex(i);
		if (pObj->getTarget() == NULL || WarModel::shardWarModel()->isDie((PersonView*)pObj->getTarget()))
		{
			pObj->setTarget(getTargetBySelfPos(1, pObj->getInfo()->posId));
		}
		pObj->getController()->checkTargetPos();
	}

	//if (stone != NULL)
	//{ 
	//	if (stone->getTarget() == NULL)
	//	{
	//		//for (int i = partener->count() - 1; i >= 0; i--) 
	//		//{
	//		if (partener->count() > 0) stone->setTarget((PartenerView*)partener->randomObject());
	//		//}
	//	}
	//	stone->getController()->checkTargetPos();
	//}

	checkDeep(); // 深度排序
}

PersonView* WarScene::getTargetBySelfPos(int selfType, int selfPos)
{
	CCArray* arr = selfType != 0 ? WarModel::shardWarModel()->getPartenerArray() : WarModel::shardWarModel()->getEnemyArray();
	
	for (int j = 0; j < 9; j++)
	{
		int tid;
		if (selfPos == 0 || selfPos == 1 || selfPos == 2) tid = posArr1[j];
		else if (selfPos == 3 || selfPos == 4 || selfPos == 5) tid = posArr2[j];
		else tid = posArr3[j];
		for (int i = arr->count() - 1; i >= 0; i--)
		{
			PartenerView* temp =  (PartenerView*)arr->objectAtIndex(i);
			if (temp->getInfo()->posId == tid) 
				return (PersonView*)temp;
		}
	}
	return NULL;
}

// 检查深度排序
void WarScene::checkDeep()
{
	CCArray* partener = WarModel::shardWarModel()->getPartenerArray();
	CCArray* enemy = WarModel::shardWarModel()->getEnemyArray();

	for (int i = enemy->count() - 1; i >= 0; i--) 
	{
		PartenerView* pObj = (PartenerView*)enemy->objectAtIndex(i);
		mLayerEntity->reorderChild(pObj, 1000 - pObj->getPositionY());
	}

	for (int i = partener->count() - 1; i >= 0; i--) 
	{
		PartenerView* pObj = (PartenerView*)partener->objectAtIndex(i);
		mLayerEntity->reorderChild(pObj, 1000 - pObj->getPositionY());
	}
	//mLayerEntity->reorderChild(hero, 1000 - hero->getPositionY());
	//mLayerEntity->reorderChild(stone, 1000 - stone->getPositionY());
}

// 触摸开始
bool WarScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->getLocation();

	mTouchX = touchPoint.x;
	mBeforX = mLayerEntity->getPositionX();
	//CCLog("start %f", mTouchX);
	//CCLog("%f,%f",touchPoint.x,touchPoint.y);
	//hero->getController()->moveTo(touchPoint);
	return true;
}

// 触摸移动
void WarScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->getLocation();
	//CCLog("%f,%f",touchPoint.x,touchPoint.y);
	
	float temp = touchPoint.x - mTouchX + mBeforX;
	if (temp <= 0)
	{
		mLayerBg->setPositionX(temp);
		mLayerEntity->setPositionX(temp);
		mLayerEffect->setPositionX(temp);
	}
	
}

// 触摸结束
void WarScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->getLocation();
	//CCLog("%f,%f",touchPoint.x,touchPoint.y);
	mTouchX = 0;
}

// 添加人物实体
void WarScene::addEntity(CCNode* entity)
{
	mLayerEntity->addChild(entity);
}

// 添加效果动画
void WarScene::addEffect(CCObject* effect)
{
	mLayerEffect->addChild((CCNode*)effect);
}

//添加当前触摸的对象
void WarScene::addTouchedEntity(CCObject* p)
{
	touchEntityArr->addObject(p);
}

//对象触摸结束
void WarScene::entityTouchEnd(CCObject* obj)
{
	PersonView* result = NULL;
	PersonView* p = NULL;
	int len = touchEntityArr->count();
	if (len > 0)
	{
		result = (PersonView*)touchEntityArr->objectAtIndex(0);
		if (len > 1)
		{
			for (int i = 1; i < len; i++)
			{
				p = (PersonView*)touchEntityArr->objectAtIndex(i);
				if (p->getPositionY() < result->getPositionY())
				{
					result = p;
				}
			}
		}
		
		if (result->getState() == DIE)
		{
			mTouchEntity = NULL;
		}
		else
		{
			mTouchEntity = result;
			for (int i = mSkillBtnArr->count() - 1; i >= 0; i--)
			{
				SkillBtn* tbn = (SkillBtn*)mSkillBtnArr->objectAtIndex(i);
				if (i >= mTouchEntity->getInfo()->getSkillArr()->count())
					tbn->setVisible(false);
				else
					tbn->setVisible(true);
			}
			//schedule(schedule_selector(WarScene::onSkillTimerHandler), 0.1f);
		}
		touchEntityArr->removeAllObjects();
	}
}

// 人物死亡
void WarScene::onEntityDie(CCObject* value)
{
	if (mTouchEntity == value)
	{
		mTouchEntity = NULL;
		//unschedule(schedule_selector(WarScene::onSkillTimerHandler));
		for (int i = mSkillBtnArr->count() - 1; i >= 0; i--)
		{
			SkillBtn* tbn = (SkillBtn*)mSkillBtnArr->objectAtIndex(i);
			tbn->setVisible(false);
		}
	}
}

// 使用技能
void WarScene::onUseSkill(CCObject* value)
{
	SkillBtn* btn = (SkillBtn*)value;
	if (mTouchEntity != NULL)
	{
		int sindex = mSkillBtnArr->indexOfObject(value);
		SkillVo* vo = (SkillVo*)mTouchEntity->getInfo()->getSkillArr()->objectAtIndex(sindex);
		if (vo->getPercent() >= 100 && mTouchEntity->getBaseId() == 2 || mTouchEntity->getBaseId() == 3) // 暂时等于2和3的可以放技能
		{
			if (mTouchEntity->getController()->useSkill(1))
				vo->setCurrentCd(vo->getMaxCd());
		}
	}
}