//-----------------------------------------------------------------------------------------------------------------------------
// ����: ���ؽ��Ƚ���
// ����: lvxiangsong
// ����: 2013-10-8
// ����: ���ؽ��Ƚ���
// �汾: 
//
// �޸���           ����	           ����		
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