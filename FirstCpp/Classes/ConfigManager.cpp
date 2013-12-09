#include "ConfigManager.h"
#include "proto/AvatarAsset.pb.h"


// singleton
static ConfigManager* mConfigManager = NULL;

ConfigManager::ConfigManager(void)
{
	init();
}

ConfigManager::~ConfigManager(void)
{
	std::map<std::string, ::google::protobuf::Message*>::iterator it;
	for(it = mMap.begin(); it != mMap.end(); it++)
	{
		delete it->second;
	}
	mMap.clear();
}

ConfigManager* ConfigManager::sharedConfigManager()
{
	if (mConfigManager == NULL)
	{
		mConfigManager = new ConfigManager();
	}
	return mConfigManager;
}

void ConfigManager::pure()
{
	if (mConfigManager)
	{
		delete mConfigManager;
		mConfigManager = NULL;
	}
}

bool ConfigManager::init()
{
	return true;
}

bool ConfigManager::initConfig()
{
	CCFileUtils::sharedFileUtils()->addSearchPath("config");
	addConfig(CONFIG_AvatarAsset);
	//addConfig(CONFIG_Wer);
	return true;
}

bool ConfigManager::addConfig(const char* fileName)
{
	std::string temp = std::string(fileName);
	if (mMap[temp] != NULL) return true;
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	unsigned long* filesize = new unsigned long;
	unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "rb", filesize);
	AvatarAssetTable* table = new AvatarAssetTable;
	table->ParseFromArray(data, (int)(&filesize));
	delete filesize;
	delete[] data;
	filesize = NULL;
	mMap[table->tname()] = table;
	CCFileUtils::sharedFileUtils()->purgeCachedEntries();
	return true;
}

::google::protobuf::Message* ConfigManager::getConfigByName(const char* fileName)
{
	std::map<std::string, ::google::protobuf::Message*>::iterator it = mMap.find(fileName);
	if(it != mMap.end())
	{
		return it->second;
	}

	return NULL;
}