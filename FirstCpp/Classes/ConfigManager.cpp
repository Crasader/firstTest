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

}

ConfigManager* ConfigManager::sharedConfigManager()
{
	if (mConfigManager == NULL)
	{
		mConfigManager = new ConfigManager();
	}
	return mConfigManager;
}

bool ConfigManager::init()
{
	return true;
}

bool ConfigManager::initConfig()
{
	CCFileUtils::sharedFileUtils()->addSearchPath("config");
	addConfig(CONFIG_AvatarAsset);
	addConfig(CONFIG_Wer);
	return true;
}

bool ConfigManager::addConfig(const char* fileName)
{
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	unsigned long* filesize = new unsigned long;
	unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "rb", filesize);
	AvatarAssetTable* table = new AvatarAssetTable;
	table->ParseFromArray(data, (int)(&filesize));
	delete filesize;
	filesize = NULL;

	mMap[table->tname()] = table;

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