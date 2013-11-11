#include "GameScene.h"
#include "war/WarScene.h"
#include "war/PartenerVo.h"
#include "war/WarModel.h"
#include "EnumCommon.h"
#include "SceneManager.h"
#include <fstream>
#include "ConfigManager.h"

//引入扩展类
#include "cocos-ext.h"
#include "loader/LoadManager.h"
#include "proto/Wer.pb.h"
#include "proto/AvatarAsset.pb.h"
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
                                origin.y + visibleSize.height - pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

	//std::fstream input("E:/cocoswork/cocos2d-x-2-1-5/projects/FirstCpp/Resources/config/AvatarAsset.dbp", ios::in | ios::binary);
	//AvatarAssetTable table;
	//table.ParseFromIstream(&input);
	//std::string sssss = table.tname();
	//CCLog("ok");
	//std::string str = ((AvatarAsset)table.tlist(0)).aname();
    CCLabelTTF* pLabel = CCLabelTTF::create("ssss", "Arial", 24);
    
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
	
	LoadManager::shardLoadManager()->addLoadItem("weapon/Weapon0.png", "weapon/Weapon0.plist", "weapon/Weapon.ExportJson");
	LoadManager::shardLoadManager()->addLoadItem("LoadUI/LoadingBar_ld03.png");
	LoadManager::shardLoadManager()->addLoadItem("a.png");
	LoadManager::shardLoadManager()->addLoadItem("b.png");
	LoadManager::shardLoadManager()->addLoadItem("c.png");
	LoadManager::shardLoadManager()->addLoadItem("d.png");
	LoadManager::shardLoadManager()->addLoadItem("e.png");
	LoadManager::shardLoadManager()->addLoadItem("f.png");
	LoadManager::shardLoadManager()->addLoadItem("g.png");
	LoadManager::shardLoadManager()->addLoadItem("h.jpg");
	LoadManager::shardLoadManager()->load(SCENE_WAR);
}

// 初始化游戏
void GameWorld::initGame(void)
{
	// 初始化游戏
	SceneManager::shardSceneManager(); // 初始化场景管理器
	ConfigManager::sharedConfigManager()->initConfig(); // 初始化配置

	//int pa[4] = {0,3,6,4};
	//CCArray* partener = WarModel::shardWarModel()->getPartenerArray();
	//for (int i = 0; i < 4; i++)
	//{
	//	PartenerView* p1 = PartenerView::create();
	//	PartenerVo* pinfo1 = PartenerVo::create();
	//	pinfo1->name = "fuwanghero";
	//	pinfo1->posId = pa[i];
	//	pinfo1->gender = 1;
	//	p1->setInfo(pinfo1);
	//	partener->addObject(p1);
	//}

	//CCLog("init over");

	//int ea[4] = {3,4,5,8};
	//CCArray* enemy = WarModel::shardWarModel()->getEnemyArray();
	//for (int i = 0; i < 4; i++)
	//{
	//	PartenerView* p1 = PartenerView::create();
	//	PartenerVo* pinfo1 = PartenerVo::create();
	//	pinfo1->name = "fuwanghero";
	//	pinfo1->posId = ea[i];
	//	pinfo1->gender = 1;
	//	p1->setInfo(pinfo1);
	//	enemy->addObject(p1);
	//}

	//CCDataReaderHelper::sharedDataReaderHelper()->addDataFromFileAsync();
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(string("fuwang/FuWang0.plist").c_str(), string("fuwang/FuWang0.png").c_str());


	//WerTable table = WerTable::default_instance();
	//::google::protobuf::RepeatedPtrField<::Wer> ve = table.tlist();
	//Wer* tile = table.add_tlist();
	//tile->set_id(1);
	//tile->set_name("song");
	//tile->set_teampoint("6_3");
	//tile->set_point(6);
	//tile->set_effect1("effect1");
	//tile->set_effect2("effect2");
	//tile->set_effect3("effect3");

	//tile = table.add_tlist();
	//tile->set_id(2);
	//tile->set_name("lxss");
	//tile->set_teampoint("6_3");
	//tile->set_point(6);
	//tile->set_effect1("effect4");
	//tile->set_effect2("effect5");
	//tile->set_effect3("effect6");

	////table.set_tname("avatarTable");
	//std::fstream out("E:/cocoswork/protoc-2.5.0-win32/dbp/Wer.dbp", ios::out | ios::binary | ios::trunc);
	//table.SerializeToOstream(&out);
	//out.close();

	/*std::fstream input("E:/cocoswork/cocos2d-x-2-1-5/projects/FirstCpp/Resources/config/AvatarAsset.dbp", ios::in | ios::binary);
	AvatarAssetTable table;
	table.ParseFromIstream(&input);
	std::string sssss = table.tname();
	AvatarAsset av = table.tlist(0);
	CCLog("ok");*/
	//for (int i = table.tlist_size() - 1; i >= 0; i--)
	//{
	//	Wer tile = table.tlist(i);
	//	CCLog("%d,%s", tile.id(), tile.name());
	//}

	//person.p
	//CCFileUtils::sharedFileUtils()->
}

void GameWorld::enterWarScene()
{
	CCLog("callback");
	CCScene* warScene = WarScene::scene();
	CCDirector::sharedDirector()->replaceScene(warScene);
}
