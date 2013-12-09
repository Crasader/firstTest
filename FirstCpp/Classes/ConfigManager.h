#pragma once

#include "cocos2d.h"
#include <map>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>


USING_NS_CC;

#define config_manager_gettile(__TABLE__, __TILE__, __NAME__, __ID__, __RESULT__) \
__TABLE__* ttt = (__TABLE__*)ConfigManager::sharedConfigManager()->getConfigByName(__NAME__); \
::google::protobuf::RepeatedPtrField< ::__TILE__ > tlist = ttt->tlist(); \
for (int index = tlist.size() - 1; index >= 0; index--) \
{ \
	if (tlist.Get(index).id() == __ID__) \
	{ \
		__RESULT__ = tlist.Mutable(index); \
		break; \
	} \
} \

static const char* CONFIG_AvatarAsset     =    "AvatarAsset.dbp";
static const char* CONFIG_Wer            =    "Wer.dbp";

class ConfigManager : CCObject
{
public:
	ConfigManager(void);
	~ConfigManager(void);

	static ConfigManager* sharedConfigManager();
	static void pure();

	bool initConfig();
	::google::protobuf::Message* getConfigByName(const char* fileName);

private:
	virtual bool init();
	bool addConfig(const char* fileName);

	std::map<std::string, ::google::protobuf::Message*> mMap;
};