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
	addChild(CCSprite::createWithSpriteFrameName("war_commonui_xt_di.png"), 0);
	addChild(CCSprite::createWithSpriteFrameName("war_commonui_xt_liti.png"), 2);
	CCSprite* progressSprite = CCSprite::createWithSpriteFrameName("war_commoneui_xt_cont.png");
	progressSprite->setCascadeColorEnabled(false);
	progressSprite->setColor(ccc3(0, 255, 0));
	mProgressBar = CCProgressTimer::create(progressSprite);
	mProgressBar->setType(kCCProgressTimerTypeBar);
	mProgressBar->setBarChangeRate(ccp(1, 0)); 
	mProgressBar->setMidpoint(ccp(0,0));
	
	addChild(mProgressBar, 1);
	setPercentage(0.999);
}

void BloodBar::onExit()
{
	if (mProgressBar != NULL)
	{
		mProgressBar->removeFromParentAndCleanup(true);
		mProgressBar = NULL;
	}
	removeAllChildrenWithCleanup(true);
	CCNode::onExit();
}

void BloodBar::setPercentage(float pro)
{
	if (pro >= 0 && pro <= 1)
	{
		int r = (1 - pro) * 255;
		int g = pro * 255;
		mProgressBar->getSprite()->setColor(ccc3(r, g, 0));
		CCProgressTo *to = CCProgressTo::create(0.3, pro*100);
		mProgressBar->runAction(to);
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
	CCNode::onEnter();
	//CCTexture2D* bgTexture = CCTextureCache::sharedTextureCache()->textureForKey("WarSkillUI/skill_kuan.png");
	//mBgImg = CCSprite::createWithTexture(bgTexture);
	mBgImg = CCSprite::createWithSpriteFrameName("skill_kuan.png");
	mBgImg->setPosition(ccp(1,-2));
	addChild(mBgImg, 1);

	mGrayImg = CCSprite::createWithSpriteFrameName("skill_1_1.png");
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
	removeAllChildrenWithCleanup(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}

void SkillBtn::setId(int value)
{
	if (mId != value)
	{
		mId = value;
		CCSprite* tps = CCSprite::createWithSpriteFrameName("skill_1_0.png");
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
// 飘血字////////////
////////////////////
BloodFont::BloodFont():labelAtlas(NULL)
{

}
BloodFont::~BloodFont()
{

}
void BloodFont::onEnter()
{
	CCNode::onEnter();
	// CCSpawn
	CCFiniteTimeAction* mv = CCSequence::create(
		CCMoveTo::create(1, CCPoint(getPositionX(), getPositionY() + 60)),
		CCDelayTime::create(0.5f),
		CCCallFunc::create(this, callfunc_selector(BloodFont::moveComplete)),
		NULL);
	runAction(mv);

	CCActionInterval* fadeto = CCFadeOut::create(1.5f);
	labelAtlas->runAction(fadeto);
}
void BloodFont::onExit()
{
	stopAllActions();
	if (labelAtlas) labelAtlas->removeAllChildrenWithCleanup(true);
	removeAllChildrenWithCleanup(true);
	CCNode::onExit();
}
bool BloodFont::init()
{
	return true;
}

void BloodFont::initBloodFont(int value, float posx, float posy)
{
	char* posid = new char[13];
	sprintf(posid, ":%d", value);
	setPositionY(posy);
	labelAtlas = CCLabelAtlas::create(posid, "warimags/redBlood.png", 18, 24, '0');
	delete[] posid;
	int www = labelAtlas->getContentSize().width;
	addChild(labelAtlas);
	setPositionX(-www / 2 + posx);
}

void BloodFont::moveComplete()
{
	removeFromParentAndCleanup(true);
}

/////////////////////
// 说话气泡//////////
////////////////////