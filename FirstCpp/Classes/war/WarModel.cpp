#include "WarModel.h"

// singleton
static WarModel* mWarModel = NULL;

WarModel::WarModel(void)
{
	mPartenerArray = CCArray::create();
	mPartenerArray->retain();
	mEnemyArray = CCArray::create();
	mEnemyArray->retain();
	//mDieArray = CCArray::create();
	//mDieArray->retain();
}


WarModel::~WarModel(void)
{
	CC_SAFE_RELEASE_NULL(mPartenerArray);
	CC_SAFE_RELEASE_NULL(mEnemyArray);
	//CC_SAFE_RELEASE_NULL(mDieArray);
	CC_SAFE_DELETE(mWarModel);
}

WarModel* WarModel::shardWarModel()
{
	if (mWarModel == NULL)
	{
		mWarModel = new WarModel();
		mWarModel->init();
	}
	return mWarModel;
}

bool WarModel::init()
{
	return true;
}

// 获取我方数据
CCArray* WarModel::getPartenerArray()
{
	return mPartenerArray;
}

// 获取地方数据
CCArray* WarModel::getEnemyArray()
{
	return mEnemyArray;
}

//CCArray* WarModel::getDieArray()
//{
//	return mDieArray;
//}

// 移除一个对象
void WarModel::removeEntity(CCObject* entity)
{
	WarModel::shardWarModel()->getPartenerArray()->removeObject(entity, true);
	WarModel::shardWarModel()->getEnemyArray()->removeObject(entity, true);
	//if (!WarModel::shardWarModel()->getEnemyArray()->containsObject(entity))
	//{
	//	WarModel::shardWarModel()->getEnemyArray()->addObject(entity);
	//}
}

bool WarModel::isDie(PersonView* obj)
{
	if (WarModel::shardWarModel()->getPartenerArray()->containsObject(obj)) return false;
	if (WarModel::shardWarModel()->getEnemyArray()->containsObject(obj)) return false;
	return true;
}