//-----------------------------------------------------------------------------------------------------------------------------
// 名称: 事件
// 作者: lvxiangsong
// 日期: 2013-10-8
// 功能: 事件
// 版本: 
//
// 修改者           日期	           内容		
// lvxiangsong      2013-10-8
//-----------------------------------------------------------------------------------------------------------------------------
#pragma once

// 场景相关
const char * const EVENT_SCENE_VIEW_MAIN = "event_scene_view_main"; // 显示主场景
const char * const EVENT_SCENE_VIEW_WAR = "event_scene_view_war"; // 事件：显示战斗场景


// 战场相关
const char * const EVENT_WAR_ADD_TOUCH_ENTITY = "event_war_add_touch_entity"; //添加触摸的对象
const char * const EVENT_WAR_ADD_TOUCH_END = "event_war_add_touch_end"; // 添加触摸对象结束
const char * const EVENT_WAR_ADD_ENTITY = "event_war_add_entity"; // 添加人物对象
const char * const EVENT_WAR_ADD_EFFECT = "event_war_add_effect"; // 添加效果动画
const char * const EVENT_WAR_ENTITY_DIE = "event_war_entity_die"; // 人物死亡
const char * const EVENT_WAR_USE_SKILL = "event_war_use_skill"; // 使用技能
const char * const EVENT_WAR_SHOW_BLOOD_FONT = "event_war_show_blood_font"; // 显示飘血字
const char * const EVENT_WAR_SELECT_HEADBTN = "event_war_select_headbtn"; // 单击头像按钮
