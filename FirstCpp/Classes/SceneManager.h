#include "cocos2d.h"
#include "cocos-ext.h"
#include "EnumEvent.h"
#include "war/WarScene.h"

using namespace cocos2d::extension;
USING_NS_CC;

class SceneManager : public CCNode
{
public:
	SceneManager(void);
	~SceneManager(void);

	static SceneManager* shardSceneManager();
	bool init();

private:
	void viewToWar(CCObject* obj); // 进入战斗场景
};