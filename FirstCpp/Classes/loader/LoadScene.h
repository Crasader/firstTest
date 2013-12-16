//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 加载进度界面
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 加载进度界面
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BaseLayer.h"

using namespace cocos2d::extension;
USING_NS_CC;

class LoadScene : public BaseLayer
{
public:
	LoadScene();
	~LoadScene();
	virtual bool init();
	virtual void onExit();
	static CCScene* scene();
	CREATE_FUNC(LoadScene);

	void setProgress(float value);
	LoadScene* getLoadScene();
private:
	UIWidget* mUi;
	UILayer* mLayer;
};