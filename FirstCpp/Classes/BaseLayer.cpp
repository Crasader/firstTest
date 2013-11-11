#include "BaseLayer.h"

BaseLayer::BaseLayer()
{
	this->setKeypadEnabled(true);
}

BaseLayer::~BaseLayer()
{
	
}

// for android
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void BaseLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}

void BaseLayer::keyMenuClicked()
{

}
#endif
// for android end

// for ios