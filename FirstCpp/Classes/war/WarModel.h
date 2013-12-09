#pragma once

#include "cocos2d.h"
#include "PersonView.h"

USING_NS_CC;

class WarModel : public CCObject
{
public:
	WarModel(void);
	~WarModel(void);

	virtual bool init();
	static WarModel* shardWarModel();
	static void pure();

	CCArray* getPartenerArray(); // ��ȡ�ҷ�����
	CCArray* getEnemyArray(); // ��ȡ�ط�����
	//CCArray* getDieArray();

	void removeEntity(CCObject* entity); // �Ƴ�һ��ʵ��
	bool isDie(PersonView* obj);

protected:
	CCArray* mPartenerArray; // �ҷ���Ӫ
	CCArray* mEnemyArray; // �ط���Ӫ
	//CCArray* mDieArray; // �������������
};

