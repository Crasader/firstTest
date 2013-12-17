#include "GameScene.h"
#include "war/WarScene.h"
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
#include "war/SkillVo.h"
#include "CommonTool.h"
#include "war/PersonView.h"
#include "war/PersonVo.h"
#include "MLua.h"
#include "LuaManager.h"
#include "DriveManager.h"
#include "I18N.h"

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
    
	pCloseItem->setPosition(ccp(-pCloseItem->getContentSize().width/2 +origin.x + visibleSize.width,
                                origin.y - pCloseItem->getContentSize().height/2 + visibleSize.height));

	CCMenuItemImage *pCloseItem1 = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(GameWorld::onCloseCpp));
	pCloseItem1->setPosition(ccp(100,100));

	CCMenuItemImage *pCloseItem2 = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(GameWorld::onCallPhone));
	pCloseItem2->setPosition(ccp(200,100));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, pCloseItem1,pCloseItem2, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

	

 //   CCLabelTTF* pLabel = CCLabelTTF::create("ssss", "Arial", 24);
 //   pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
 //                           origin.y + visibleSize.height - pLabel->getContentSize().height));
 //   this->addChild(pLabel, 1);

	//pLabel->setString("hello world");

	CCLabelTTF* plll = CCLabelTTF::create("sasdf", "Arial", 30);
	this->addChild(plll);

	return true;

    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite, 0);
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

void GameWorld::onCloseCpp(CCObject* pSender)
{
	LuaManager::pure();
	I18N::pure();
	DriveManager::pure();
	google::protobuf::ShutdownProtobufLibrary();
	PersonView::pure();
	CommonTool::pure();
	SceneManager::pure();
	ConfigManager::pure();
	WarModel::pure();
	LoadManager::pure();
	CCScriptEngineManager::sharedManager()->removeScriptEngine();
	
	CCDirector::sharedDirector()->stopAnimation();
	//CCDirector::sharedDirector()->purgeCachedData();
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
	GUIReader::purgeGUIReader();
	CCArmatureDataManager::purge();
	CCDataReaderHelper::purge();
	DictionaryHelper::purgeDictionaryHelper();
	CCScriptEngineManager::purgeSharedManager();
	CCDirector::sharedDirector()->end();
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

// 初始化游戏
void GameWorld::initGame(void)
{
	// 初始化游戏
	//LuaManager::shareLuaManager()->getMLua()->LoadLuaFile("mlua.lua");
	LuaManager::shareLuaManager()->getMLua()->LoadLuaString("setFormation('101011001', '000040000');");
	
	//LuaManager::shareLuaManager()->getMLua()->LoadString(CCFileUtils::sharedFileUtils()->fullPathForFilename("mlua.lua"));
	//for (int i = 0; i < 9; i++)
	//{
	//	LuaManager::shareLuaManager()->aTeam[i] = 1;
	//	LuaManager::shareLuaManager()->bTeam[i] = 2;
	//}
	SceneManager::shardSceneManager(); // 初始化场景管理器
	ConfigManager::sharedConfigManager()->initConfig(); // 初始化配置

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

void GameWorld::onCallPhone(CCObject* pSender)
{
	DriveManager::sharedDriveManager()->showTestDialog();
}