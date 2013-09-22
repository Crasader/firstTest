#include "GameScene.h"
#include "war/WarScene.h"
#include "war/PartenerVo.h"
#include "war/WarModel.h"
#include "EnumCommon.h"
#include "SceneManager.h"

//引入扩展类
#include "cocos-ext.h"
#include "loader/LoadManager.h"
//添加命名空间
using namespace cocos2d::extension;

USING_NS_CC;

double getRandom(double start, double end)
{
	return start+(end-start)*rand()/(RAND_MAX + 1.0);
}

CCScene* GameWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameWorld *layer = GameWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	initGame(); // 初始化游戏
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

	////创建一个UILayer层
	//UILayer*   ul =UILayer::create();
	////开启刷新函数
	//ul->scheduleUpdate();
	////将UILayer层加入到当前的场景
	//this->addChild(ul);
	////使用json文件给Layer层添加CocoStudio生成的控件
	//ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("UIEditorTest/UIEditorTest_1.json"));


	//首先读取png,plist和ExportJson/json文件，
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("ActionEditor/Cowboy0.png", "ActionEditor/Cowboy0.plist", "ActionEditor/Cowboy.ExportJson");
	//然后创建armature类，并将进行初始化
	CCArmature *armature = CCArmature::create("Cowboy");
	//然后选择播放动画0，并进行缩放和位置设置
	armature->getAnimation()->playByIndex(1);
	//该模板中共制作了三个动画，你可以将索引修改为0/1/2中的任意值来查看不同效果
	armature->setScale(0.5f);
	armature->setPosition(ccp(visibleSize.width * 0.5, visibleSize.height * 0.5));
	//最后将armature添加到场景中
	this->addChild(armature,2);

	armature = CCArmature::create("Cowboy");
	//然后选择播放动画0，并进行缩放和位置设置
	armature->getAnimation()->playByIndex(2);
	//该模板中共制作了三个动画，你可以将索引修改为0/1/2中的任意值来查看不同效果
	armature->setScale(0.5f);
	armature->setPosition(ccp(visibleSize.width * 0.7, visibleSize.height * 0.7));
	//最后将armature添加到场景中
	this->addChild(armature,3);
    
    return true;
}


void GameWorld::menuCloseCallback(CCObject* pSender)
{
	////创建一个新的场景
	//CCScene * newscene  = CCScene::create();
	////从CocoStudio场景编辑器生成的数据生成根节点
	//CCNode *pNode = CCSSceneReader::sharedSceneReader()->createNodeWithSceneFile("SceneEditorTest/SceneEditorTest.json");

	////播放背景音乐
	//CCComAudio *pAudio = (CCComAudio*)(pNode->getComponent("Audio"));
	////pAudio->playBackgroundMusic(pAudio->getFile(), pAudio->isLoop());
	//pAudio->playBackgroundMusic(pAudio->getFile(), true);
	////给蝴蝶鱼配置动画
	//CCComRender *pFishRender = (CCComRender*)(pNode->getChildByTag(10010)->getComponent( "butterFlyFish"));
	//CCArmature *pButterFlyFish= (CCArmature *)(pFishRender->getRender());
	//pButterFlyFish->getAnimation()->playByIndex(0);
	//newscene->addChild(pNode, 0, 1);
	////切换到新的场景
	//CCDirector::sharedDirector()->replaceScene(newscene);

	
	LoadManager::shardLoadManager()->addLoadItem("fuwang/FuWang0.png", "fuwang/FuWang0.plist", "fuwang/FuWang.ExportJson");
	LoadManager::shardLoadManager()->addLoadItem("weapon/Weapon0.png", "weapon/Weapon0.plist", "weapon/Weapon.ExportJson");
	LoadManager::shardLoadManager()->load(SCENE_WAR);
}

// 初始化游戏
void GameWorld::initGame(void)
{
	// 初始化游戏
	SceneManager::shardSceneManager(); // 初始化场景管理器

	// for test 初始化双方阵营数据
	//int temp[9];
	//int icount = 0;
	//srand(unsigned(time(0)));
	//while (icount < 9)
	//{
	//	int idata = rand()%9;
	//	for (int i = 0; i < 9; i++)
	//	{
	//		if (temp[i] == idata) break;
	//		temp[i] = idata;
	//		icount++;
	//	}
	//}

	//CCArray* partener = WarModel::shardWarModel()->getPartenerArray();
	//for (int i = 0; i < 3; i++)
	//{
	//	PartenerView* p1 = PartenerView::create();
	//	PartenerVo* pinfo1 = PartenerVo::create();
	//	pinfo1->name = "fuwanghero";
	//	pinfo1->posId = i;
	//	pinfo1->gender = 1;
	//	pinfo1->pngName = "fuwang/FuWang0.png";
	//	pinfo1->xmlName = "fuwang/FuWang0.plist";
	//	pinfo1->jsonName = "fuwang/FuWang.ExportJson";
	//	p1->setInfo(pinfo1);
	//	partener->addObject(p1);
	//}

	//CCArray* enemy = WarModel::shardWarModel()->getEnemyArray();
	//for (int i = 0; i < 3; i++)
	//{
	//	PartenerView* p1 = PartenerView::create();
	//	PartenerVo* pinfo1 = PartenerVo::create();
	//	pinfo1->name = "fuwanghero";
	//	pinfo1->posId = i;
	//	pinfo1->gender = 1;
	//	pinfo1->pngName = "fuwang/FuWang0.png";
	//	pinfo1->xmlName = "fuwang/FuWang0.plist";
	//	pinfo1->jsonName = "fuwang/FuWang.ExportJson";
	//	p1->setInfo(pinfo1);
	//	enemy->addObject(p1);
	//}

	//CCDataReaderHelper::sharedDataReaderHelper()->addDataFromFileAsync();
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(string("fuwang/FuWang0.plist").c_str(), string("fuwang/FuWang0.png").c_str());
	

}

void GameWorld::enterWarScene()
{
	CCLog("callback");
	CCScene* warScene = WarScene::scene();
	CCDirector::sharedDirector()->replaceScene(warScene);
}
