#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ControllerListener.h"
#include "ControllerBase.h"
#include "PersonVo.h"

using namespace cocos2d::extension;

USING_NS_CC;

class PersonView : public CCNode, public ControllerListener
{
public:
	PersonView(void);
	~PersonView(void);

	// function
	void setAvatar(CCArmature* avatar); // 设置形象
	void setController(ControllerBase* controller); // 设置控制器
	void removeController(); // 移除控制器
	virtual ControllerBase* getController(); // 获取控制器
	void setTarget(CCNode* target); //设置进攻的目标
	bool isTarget() const; // 是否有进攻目标
	CCNode* removeTarget(); // 移除进攻目标
	virtual void setInfo(PersonVo* info); // 设置基本信息
	virtual PersonVo* getInfo() const; // 获取基本信息

	//实现ControllerListener接口
	void setSimplePostion(float x, float y); // 设置位置
	virtual CCPoint getCurPostion(); // 获取位置
	virtual void changeDirection(PERSON_DIRECTION dir); // 改变方向
	virtual PERSON_DIRECTION getDirection(); // 获取方向
	virtual CCNode* getTarget(); // 获取进攻目标
	virtual void changeState(PERSON_STATE state); // 改变状态
	virtual PERSON_STATE getState(); // 获取当前状态
	virtual PersonVo* getSelfInfo(); // 获取单位的数据信息
	virtual void dieOut(); // 死出去
	virtual CCNode* getSelfEntity(); // 获取自己

protected:
	CCArmature* mAvatar; // 形象
	ControllerBase* mController; // 控制器
	CCNode* mTarget; // 进攻的目标
	PERSON_STATE mCurState; // 当前状态
	PersonVo* mInfo; // 基本信息
	PERSON_DIRECTION mDirection; // 方向
	
	void onAnimationComplete(CCArmature * arm, MovementEventType etype, const char * ename);
	
};

