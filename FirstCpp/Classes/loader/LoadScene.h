#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d::extension;
USING_NS_CC;

class LoadScene : public CCLayer
{
public:
	virtual bool init();
	static CCScene* scene();

	CREATE_FUNC(LoadScene);

protected:
private:
};