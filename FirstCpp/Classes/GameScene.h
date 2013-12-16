#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "BaseLayer.h"

class GameWorld : public BaseLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void onCloseCpp(CCObject* pSender);
	void onCallPhone(CCObject* pSender); // 调用手机函数
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameWorld);

private:
	void initGame(void); // 初始化游戏
};

#endif // __HELLOWORLD_SCENE_H__
