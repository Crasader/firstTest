#include "CommonTool.h"

// singleton
static CommonTool* mCommonTool = NULL;

CommonTool::CommonTool()
{

}

CommonTool::~CommonTool()
{
	
}

CommonTool* CommonTool::shardCommonTool()
{
	if (mCommonTool == NULL)
	{
		mCommonTool = new CommonTool();
		mCommonTool->init();
	}
	return mCommonTool;
}

bool CommonTool::init()
{
	return true;
}

void CommonTool::pure()
{
	CC_SAFE_DELETE(mCommonTool);
}

CCMenuItemImage* CommonTool::createCCMenuItemImage(const char *normalImage, const char *selectedImage, const char *disabledImage, CCObject* target, SEL_MenuHandler selector)
{
	CCMenuItemImage *pItem = CCMenuItemImage::create();
	pItem->initWithTarget(target, selector);
	if (normalImage) pItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normalImage));
	if (selectedImage) pItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(selectedImage));
	if (disabledImage) pItem->setDisabledSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(disabledImage));
	return pItem;
}