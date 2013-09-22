#include "WarModel.h"

// singleton
static WarModel* mWarModel = NULL;

WarModel::WarModel(void)
{
	mPartenerArray = CCArray::create();
	mPartenerArray->retain();
	mEnemyArray = CCArray::create();
	mEnemyArray->retain();
}


WarModel::~WarModel(void)
{
	CC_SAFE_RELEASE_NULL(mPartenerArray);
	CC_SAFE_RELEASE_NULL(mEnemyArray);
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