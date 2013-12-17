#include "WarScene.h"
#include "cocos-ext.h"
#include "SimpleControll.h"
#include "WarModel.h"
#include "EnumCommon.h"
#include "ConfigManager.h"
#include "EnumEvent.h"
#include "SkillVo.h"
#include "CommonTool.h"
#include "GameScene.h"
#include "loader\LoadManager.h"
#include "PersonVo.h"
#include "LuaManager.h"
#include "I18N.h"

using namespace cocos2d::extension;
USING_NS_CC;

//-----------------------------------------------------------------------------------------------------------------------------
WarScene::WarScene(void):mTouchEntity(NULL)
{
	touchEntityArr = CCArray::create();
	CC_SAFE_RETAIN(touchEntityArr);
	mSkillBtnArr = CCArray::create();
	CC_SAFE_RETAIN(mSkillBtnArr);
	mHeadBtnArr = CCArray::create();
	CC_SAFE_RETAIN(mHeadBtnArr);
}

//-----------------------------------------------------------------------------------------------------------------------------
WarScene::~WarScene(void)
{

	CC_SAFE_RELEASE_NULL(touchEntityArr);
	CC_SAFE_RELEASE_NULL(mSkillBtnArr);
	CC_SAFE_RELEASE_NULL(mHeadBtnArr);
}

//-----------------------------------------------------------------------------------------------------------------------------
void WarScene::onEnter()
{
	CCLayer::onEnter();

	//// 创建返回按钮
	//CCMenuItemImage *pCloseItem = CommonTool::shardCommonTool()->createCCMenuItemImage(
	//	"war_commonui_back.png",
	//	"war_commonui_back.png",
	//	NULL,
	//	this,
	//	menu_selector(WarScene::menuCloseCallback));
	//pCloseItem->setPosition(ccp(960 - pCloseItem->getContentSize().width / 2, 640 - pCloseItem->getContentSize().height / 2));
	//CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	//pMenu->setPosition(CCPointZero);
	//addChild(pMenu);
	//return;

	// 添加侦听事件
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::addTouchedEntity), EVENT_WAR_ADD_TOUCH_ENTITY, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::entityTouchEnd), EVENT_WAR_ADD_TOUCH_END, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::addEffect), EVENT_WAR_ADD_EFFECT, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::onEntityDie), EVENT_WAR_ENTITY_DIE, NULL);
	//CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::onUseSkill), EVENT_WAR_USE_SKILL, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::addEffect), EVENT_WAR_SHOW_BLOOD_FONT, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(WarScene::onSelectHeadbtn), EVENT_WAR_SELECT_HEADBTN, NULL);

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

	mBgUILayer = UILayer::create();
	addChild(mBgUILayer, 0);
	UIWidget* root = GUIReader::shareReader()->widgetFromJsonFile("WarUI_1.json");
	root->setPosition(origin);
	mBgUILayer->addWidget(root);

	mPreUILayer = UILayer::create();
	addChild(mPreUILayer, 1);
	UIWidget* preui = GUIReader::shareReader()->widgetFromJsonFile("WarPreUI_1/WarPreUI_1.json");
	preui->setPosition(ccp(0,0));
	mPreUILayer->addWidget(preui);

	string labelstr = I18N::sharedI18N()->getStringArgs("chinese", "five", 1.324f, 21);
	CCLabelTTF* pLabel = CCLabelTTF::create(labelstr.c_str(), "Arial", 24);
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height - pLabel->getContentSize().height - 100));
	mLayerUI->addChild(pLabel);

	//CCDictionary* strings = CCDictionary::createWithContentsOfFile("i18n_cn.xml");
	//const char* str = ((CCString*)strings->objectForKey("japanese"))->m_sString.c_str();
	//pLabel->setString(str);

	CCArray* partener = WarModel::shardWarModel()->getPartenerArray();
	CCArray* enemy = WarModel::shardWarModel()->getEnemyArray();

	SimpleControll* movecontroll = NULL;
	for (int i = partener->count() - 1; i >= 0; i--) 
	{
		PersonView* pObj = (PersonView*)partener->objectAtIndex(i);
		char* posid = new char[12];
		sprintf(posid, "left%d", pObj->getInfo()->posId);
		CCPoint tp = root->getChildByName("ImageView")->getChildByName(posid)->getPosition();
		pObj->setPosition(ccp(tp.x + origin.x, tp.y + origin.y));
		delete[] posid;

		movecontroll = SimpleControll::create();
		pObj->setController(movecontroll);

		addEntity(pObj);

		HeadBtn* hbtn1 = HeadBtn::create();
		mLayerUI->addChild(hbtn1);
		hbtn1->setVisible(false);
		hbtn1->setTaget(pObj);
		hbtn1->setPosition(ccp(origin.x + 50, origin.y + 100 * i + 80));
		mHeadBtnArr->addObject(hbtn1);
		pObj->setHeadBtn(hbtn1);
	}

	for (int i = enemy->count() - 1; i >= 0; i--) 
	{
		PersonView* pObj = (PersonView*)enemy->objectAtIndex(i);
		char* posid = new char[12];
		sprintf(posid, "right%d", pObj->getInfo()->posId);
		CCPoint tp = root->getChildByName("ImageView")->getChildByName(posid)->getPosition();
		pObj->setPosition(ccp(tp.x + origin.x, tp.y + origin.y));
		delete[] posid;

		movecontroll = SimpleControll::create();
		
		pObj->setController(movecontroll);

		addEntity(pObj);
		pObj->changeDirection(DIR_LEFT);
	}

	initUI();

	scheduleUpdate();
}

//-----------------------------------------------------------------------------------------------------------------------------
void WarScene::onExit()
{
	
	removeAllChildrenWithCleanup(true);

	CCLayer::onExit();
}

//-----------------------------------------------------------------------------------------------------------------------------
CCScene* WarScene::scene()
{
	CCScene* mScene = CCScene::create();
	WarScene* mWarScene = WarScene::create();

	mScene->addChild(mWarScene, 0, 1);

	return mScene;
}

//-----------------------------------------------------------------------------------------------------------------------------
bool WarScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	return true;

}

//-----------------------------------------------------------------------------------------------------------------------------
void WarScene::purgeSelf()
{
	// 移除侦听事件
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_SELECT_HEADBTN);
	//CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_USE_SKILL);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_ENTITY_DIE);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_ADD_EFFECT);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_ADD_TOUCH_END);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_ADD_TOUCH_ENTITY);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_WAR_SHOW_BLOOD_FONT);

	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	unschedule(schedule_selector(WarScene::onSkillTimerHandler));
	unschedule(schedule_selector(WarScene::onTimerHandler));
	unscheduleUpdate();

	mSkillBtnArr->removeAllObjects();
	mHeadBtnArr->removeAllObjects();
	this->removeAllChildrenWithCleanup(true);
}

//-----------------------------------------------------------------------------------------------------------------------------
void WarScene::initUI()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//for (int i = 0; i < 5; i++)
	//{
	//	SkillBtn* sbtn0 = SkillBtn::create();
	//	sbtn0->setPosition(ccp(origin.x + 60 + 110*i, origin.y - 60 + visibleSize.height));
	//	sbtn0->setVisible(false);
	//	mLayerUI->addChild(sbtn0);
	//	mSkillBtnArr->addObject(sbtn0);
	//}

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

//-----------------------------------------------------------------------------------------------------------------------------
// 返回按钮事件处理
void WarScene::menuCloseCallback(CCObject* pSender)
{
	purgeSelf();

	////CCDirector::sharedDirector()->stopAnimation();
	//CCDirector::sharedDirector()->purgeCachedData();
	//CCTextureCache::sharedTextureCache()->removeAllTextures();
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
	//ActionManager::shareManager()->releaseActions();
	//ActionManager::purgeActionManager();
	//GUIReader::shareReader()->purgeGUIReader();
	//CCArmatureDataManager::purge();
	//CCDataReaderHelper::purge();
	////DictionaryHelper::purgeDictionaryHelper();
	////CCScriptEngineManager::purgeSharedManager();

	//CCScene *pScene = GameWorld::scene();
	//CCDirector::sharedDirector()->replaceScene(pScene);

	LoadManager::shardLoadManager()->load(SCENE_MAIN);
	return;

	LuaManager* luamanager = LuaManager::shareLuaManager();
	CCArray* partener = WarModel::shardWarModel()->getPartenerArray();
	partener->removeAllObjects();
	for (int i = 0; i < 9; i++)
	{
		if (luamanager->aTeam[i] == 0) continue;
		PersonView* p1 = PersonView::create();
		PersonVo* pinfo1 = PersonVo::create();
		pinfo1->name = "fuwanghero";
		pinfo1->posId = i;
		pinfo1->gender = 1;
		SkillVo* svo = SkillVo::create();
		svo->setMaxCd(10 * i);
		pinfo1->getSkillArr()->addObject(svo);
		p1->setBaseId(luamanager->aTeam[i]);
		p1->setInfo(pinfo1);
		partener->addObject(p1);
	}

	CCLog("init over");

	CCArray* enemy = WarModel::shardWarModel()->getEnemyArray();
	enemy->removeAllObjects();
	for (int i = 0; i < 9; i++)
	{
		if (luamanager->bTeam[i] == 0) continue;
		PersonView* p1 = PersonView::create();
		PersonVo* pinfo1 = PersonVo::create();
		pinfo1->name = "fuwanghero";
		pinfo1->posId = i;
		pinfo1->gender = 1;
		p1->setBaseId(luamanager->bTeam[i]);
		p1->setInfo(pinfo1);
		enemy->addObject(p1);
	}

	int arr[] = {1, 2, 3, 4,5,6};
	for (int i = 0; i < 6; i++)
	{
		AvatarAsset* av = NULL;
		config_manager_gettile(AvatarAssetTable, AvatarAsset, CONFIG_AvatarAsset, arr[i], av);

		string aname = av->name();
		int nameLen = aname.length();
		char* cPng = new char[nameLen + 13];
		sprintf(cPng, "avatar/%s0.png", aname.c_str());
		char* cXml = new char[nameLen + 15];
		sprintf(cXml, "avatar/%s0.plist", aname.c_str());
		char* cJson = new char[nameLen + 20];
		sprintf(cJson, "avatar/%s.ExportJson", aname.c_str());
		LoadManager::shardLoadManager()->addLoadItem(cPng, cXml, cJson);
		delete cPng;
		delete cXml;
		delete cJson;
	}

	LoadManager::shardLoadManager()->addLoadItem("weapon/Bullet0.png", "weapon/Bullet0.plist", "weapon/Bullet.ExportJson");
	LoadManager::shardLoadManager()->addLoadItem("WarSkillUI/WarSkillUI0.png", "WarSkillUI/WarSkillUI0.plist");
	LoadManager::shardLoadManager()->addLoadItem("warimags/WarCommonUI0.png", "warimags/WarCommonUI0.plist");
	LoadManager::shardLoadManager()->addLoadItem("warimags/redBlood.png");
	LoadManager::shardLoadManager()->load(SCENE_WAR);
}

//-----------------------------------------------------------------------------------------------------------------------------
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
			//if (mTouchEntity != NULL && mTouchEntity == hero)
			//{
			//	SkillBtn* tbn = (SkillBtn*)mSkillBtnArr->objectAtIndex(i);
			//	tbn->setId(j*10 + i);
			//	tbn->setPercent(vo->getPercent());
			//	
			//}
		}
	}

	for (int k = mHeadBtnArr->count() - 1; k >= 0; k--)
	{
		HeadBtn* headbtn = (HeadBtn*)mHeadBtnArr->objectAtIndex(k);
		headbtn->checkSkillTime();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// 每帧执行
void WarScene::update(float delta)
{
	
}

//-----------------------------------------------------------------------------------------------------------------------------
// 该函数每秒钟执行一次
void WarScene::onTimerHandler(float dt)
{
	CCArray* partener = WarModel::shardWarModel()->getPartenerArray();
	for (int i = partener->count() - 1; i >= 0; i--) 
	{
		PersonView* pObj = (PersonView*)partener->objectAtIndex(i);
		if (pObj->getTarget() == NULL || WarModel::shardWarModel()->isDie((PersonView*)pObj->getTarget()))
		{
			pObj->setTarget(getTargetBySelfPos(0, pObj->getInfo()->posId));
		}
		pObj->getController()->checkTargetPos();
	}

	CCArray* enemy = WarModel::shardWarModel()->getEnemyArray();
	for (int i = enemy->count() - 1; i >= 0; i--) 
	{
		PersonView* pObj = (PersonView*)enemy->objectAtIndex(i);
		if (pObj->getTarget() == NULL || WarModel::shardWarModel()->isDie((PersonView*)pObj->getTarget()))
		{
			pObj->setTarget(getTargetBySelfPos(1, pObj->getInfo()->posId));
		}
		pObj->getController()->checkTargetPos();
	}
	checkDeep(); // 深度排序
}

//-----------------------------------------------------------------------------------------------------------------------------
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
			PersonView* temp =  (PersonView*)arr->objectAtIndex(i);
			if (temp->getInfo()->posId == tid) 
				return (PersonView*)temp;
		}
	}
	return NULL;
}

//-----------------------------------------------------------------------------------------------------------------------------
// 检查深度排序
void WarScene::checkDeep()
{
	CCArray* partener = WarModel::shardWarModel()->getPartenerArray();
	CCArray* enemy = WarModel::shardWarModel()->getEnemyArray();

	for (int i = enemy->count() - 1; i >= 0; i--) 
	{
		PersonView* pObj = (PersonView*)enemy->objectAtIndex(i);
		mLayerEntity->reorderChild(pObj, 1000 - pObj->getPositionY());
	}

	for (int i = partener->count() - 1; i >= 0; i--) 
	{
		PersonView* pObj = (PersonView*)partener->objectAtIndex(i);
		mLayerEntity->reorderChild(pObj, 1000 - pObj->getPositionY());
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// 触摸开始
bool WarScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	mTouchX = pTouch->getLocation().x;
	mBeforX = mLayerEntity->getPositionX();
	return true;
}

//-----------------------------------------------------------------------------------------------------------------------------
// 触摸移动
void WarScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->getLocation();
	float temp = touchPoint.x - mTouchX + mBeforX;
	if (temp <= 0)
	{
		mLayerBg->setPositionX(temp);
		mLayerEntity->setPositionX(temp);
		mLayerEffect->setPositionX(temp);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
// 触摸结束
void WarScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->getLocation();
	mTouchX = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------
// 添加人物实体
void WarScene::addEntity(CCNode* entity)
{
	mLayerEntity->addChild(entity);
	mLayerEntity->reorderChild(entity, 1000 - entity->getPositionY());
}

//-----------------------------------------------------------------------------------------------------------------------------
// 添加效果动画
void WarScene::addEffect(CCObject* effect)
{
	mLayerEffect->addChild((CCNode*)effect);
}

//-----------------------------------------------------------------------------------------------------------------------------
//添加当前触摸的对象
void WarScene::addTouchedEntity(CCObject* p)
{
	touchEntityArr->addObject(p);
}

//-----------------------------------------------------------------------------------------------------------------------------
//对象触摸结束
void WarScene::entityTouchEnd(CCObject* obj)
{
	//return;

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
				if (i >= int(mTouchEntity->getInfo()->getSkillArr()->count()))
					tbn->setVisible(false);
				else
					tbn->setVisible(true);
			}
			//schedule(schedule_selector(WarScene::onSkillTimerHandler), 0.1f);
		}
		touchEntityArr->removeAllObjects();
	}
}

//-----------------------------------------------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------------------------------------------------
//// 使用技能
//void WarScene::onUseSkill(CCObject* value)
//{
//	SkillBtn* btn = (SkillBtn*)value;
//	if (mTouchEntity != NULL)
//	{
//		int sindex = mSkillBtnArr->indexOfObject(value);
//		SkillVo* vo = (SkillVo*)mTouchEntity->getInfo()->getSkillArr()->objectAtIndex(sindex);
//		if (vo->getPercent() >= 100 && mTouchEntity->getBaseId() == 2 || mTouchEntity->getBaseId() == 3) // 暂时等于2和3的可以放技能
//		{
//			if (mTouchEntity->getController()->useSkill(1))
//				vo->setCurrentCd(vo->getMaxCd());
//		}
//	}
//}

//-----------------------------------------------------------------------------------------------------------------------------
// 单击头像按钮
void WarScene::onSelectHeadbtn(CCObject* value)
{
	for (int i = mHeadBtnArr->count() - 1; i >= 0; i--)
	{
		HeadBtn* btn = (HeadBtn*)mHeadBtnArr->objectAtIndex(i);
		btn->setSelected(btn == value);
	}
}

//-----------------------------------------------------------------------------------------------------------------------------