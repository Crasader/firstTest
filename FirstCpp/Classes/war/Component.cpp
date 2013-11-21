#include "Component.h"
#include "EnumEvent.h"
///////////////////////
// 血条////////////////
//////////////////////
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

//////////////////////
// 技能按钮 //////////
/////////////////////
SkillBtn::SkillBtn()
{

}

SkillBtn::~SkillBtn()
{

}

bool SkillBtn::init()
{
	
	return true;
}

void SkillBtn::onEnter()
{
	CCTexture2D* bgTexture = CCTextureCache::sharedTextureCache()->textureForKey("WarSkillUI/skill_kuan.png");
	mBgImg = CCSprite::createWithTexture(bgTexture);
	mBgImg->setPosition(ccp(1,-2));
	addChild(mBgImg, 1);

	CCTexture2D* grayTextrue = CCTextureCache::sharedTextureCache()->textureForKey("WarSkillUI/skill_1_1.png");
	mGrayImg = CCSprite::createWithTexture(grayTextrue);
	addChild(mGrayImg);

	mPro = CCProgressTimer::create(mGrayImg);
	mPro->setType(kCCProgressTimerTypeBar);
	mPro->setBarChangeRate(ccp(0, 1)); 
	mPro->setMidpoint(ccp(0,0));
	addChild(mPro);

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, true);
}

void SkillBtn::onExit()
{
	mBgImg->removeFromParentAndCleanup(true);
	mGrayImg->removeFromParentAndCleanup(true);

	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void SkillBtn::setId(int value)
{
	if (mId != value)
	{
		mId = value;
		CCTexture2D* tpt = CCTextureCache::sharedTextureCache()->textureForKey("WarSkillUI/skill_1_0.png");
		CCSprite* tps = CCSprite::createWithTexture(tpt);
		if (mPro != NULL)
			mPro->removeFromParentAndCleanup(true);
		mPro = CCProgressTimer::create(tps);
		mPro->setType(kCCProgressTimerTypeBar);
		mPro->setBarChangeRate(ccp(0, 1)); 
		mPro->setMidpoint(ccp(0,0));
		addChild(mPro);
	}
}

void SkillBtn::setPercent(float value)
{
	if (value >= 0 && value <= 100)
	{
		mPro->setPercentage(value);
	}
}

// 触摸开始
bool SkillBtn::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCSize siz = mPro->getContentSize();
	CCPoint tlo = pTouch->getLocationInView();
	// 把点的坐标转换成OpenGL坐标（左下角为原点）
	tlo = CCDirector::sharedDirector()->convertToGL(tlo);
	// 把OpenGL的坐标转换成CCLayer的坐标
	CCPoint lo = convertToNodeSpace(tlo);
	float a = siz.width / 2;
	float b = siz.height / 2;
	bool flag = lo.x > -a && lo.x < a && lo.y > -b && lo.y < b;
	flag = flag && this->isVisible();
	if (flag)
	{
		if (mPro->getPercentage() >= 100)
			CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_WAR_USE_SKILL, this);
		return true;
	}
	else
	{
		return false;
	}
}

// 触摸结束
void SkillBtn::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

/////////////////////
// 说话气泡//////////
////////////////////