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
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameWorld);

private:
	void initGame(void); // ≥ı ºªØ”Œœ∑
};

#endif // __HELLOWORLD_SCENE_H__
