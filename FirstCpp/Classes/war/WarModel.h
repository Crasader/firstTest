#pragma once

#include "cocos2d.h"

USING_NS_CC;

class WarModel : public CCObject
{
public:
	WarModel(void);
	~WarModel(void);

	virtual bool init();
	static WarModel* shardWarModel();

	CCArray* getPartenerArray(); // ��ȡ�ҷ�����
	CCArray* getEnemyArray(); // ��ȡ�ط�����

protected:
	CCArray* mPartenerArray; // �ҷ���Ӫ
	CCArray* mEnemyArray; // �ط���Ӫ
};

