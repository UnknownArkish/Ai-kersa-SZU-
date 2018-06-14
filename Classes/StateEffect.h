#pragma once

#ifndef _STATE_EFFECT_H_
#define _STATE_EFFECT_H_

#include"BaseEffect.h"
#include"BaseState.h"

class StateEffect : public BaseEffect {
public:
	//状态类型、状态图标、状态名字、状态说明、持续回合、是否可以作用、是否暂时状态、、改变的属性（可选）、改变量（可选）
	static StateEffect* create( TargetType target_type , StateType state_type, std::string picPath, std::string name, std::string info, int rounds, 
		bool isCanEffect, bool isTemporary , bool isCanOverlay,Property property = Property::Health, int* property_change = 0);

private:
	virtual bool init(TargetType target_type, StateType type, std::string picPath, std::string name, std::string info, int rounds, bool isCanEffect, 
		bool isTemporary, bool isCanOverlay, Property property = Property::Health, int* property_change = 0);

	virtual void effect(Target& target);
private:
	StateType m_state_type;
	std::string m_picPath;	//用以生成状态图片
	std::string m_name;	//用以生成状态名字
	std::string m_info;	//用以生成状态说明

	int m_continues_rouds;	//持续回合数，-1为永久

	bool m_isCanEffect;	//是否可以作用
	bool m_isTemporary;	//是否为暂时状态
	bool m_isCanOverlay;	//是否可以叠加

	Property m_property;
	int* m_property_change;
};


#endif // _STATE_EFFECT_H_
