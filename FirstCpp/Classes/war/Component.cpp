#include "Component.h"

// 血条

BloodBar::BloodBar():mProgressBar(NULL)
{
	
}

BloodBar::~BloodBar()
{
	
}

bool BloodBar::init()
{
	return true;
}

void BloodBar::onEnter()
{
	CCNode::onEnter();

	CCTexture2D* bloodTexture = CCTextureCache::sharedTextureCache()->textureForKey("LoadUI/LoadingBar_ld03.png");
	CCSprite* progressSprite = CCSprite::createWithTexture(bloodTexture);
	//addChild(progressSprite, 1);
	mProgressBar = CCProgressTimer::create(progressSprite);
	mProgressBar->setType(kCCProgressTimerTypeBar);
	mProgressBar->setBarChangeRate(ccp(1, 0)); 
	mProgressBar->setMidpoint(ccp(0,0));
	addChild(mProgressBar, 1);
	setPercentage(0.999);
	//mProgressBar->setPercentage(99.9);

	
}

void BloodBar::onExit()
{
	if (mProgressBar != NULL)
	{
		mProgressBar->removeFromParentAndCleanup(true);
		mProgressBar = NULL;
	}
}

void BloodBar::setPercentage(float pro)
{
	if (pro >= 0 && pro <= 1)
	{
		CCProgressTo *to = CCProgressTo::create(0.3, pro*100);
		mProgressBar->runAction(to);
		//mProgressBar->setPercentage(pro * 100);
	}
}

// 说话气泡