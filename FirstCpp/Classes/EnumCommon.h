//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 共用枚举
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 共用枚举
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum SCENE{SCENE_MAIN = 10, SCENE_WAR}; // 场景枚举

const char * const STATE_STAND = "stand"; // 站立
const char * const STATE_SKILL = "skill"; // 技能
const char * const STATE_RUN = "run"; // 跑步
const char * const STATE_EMBATTLED = "embattled"; // 被攻击
const char * const STATE_ATTACK = "attack"; // 攻击
const char * const STATE_DIE = "die"; // 死亡
