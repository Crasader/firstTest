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

// ��ȡ�ҷ�����
CCArray* WarModel::getPartenerArray()
{
	return mPartenerArray;
}

// ��ȡ�ط�����
CCArray* WarModel::getEnemyArray()
{
	return mEnemyArray;
}

//CCArray* WarModel::getDieArray()
//{
//	return mDieArray;
//}

// �Ƴ�һ������
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