#pragma once

#ifndef _PROPERTY_CHANGE_EFFECT_H_
#define _PROPERTY_CHANGE_EFFECT_H_

#include"BaseEffect.h"
#include"Player.h"
#include"PropertyChangeState.h"

class PropertyChangeEffect :public BaseEffect {
public:
	//是否作用于敌人、改变哪个属性、该属性改变值，（后面为PropertyChangeState相关参数）
	static PropertyChangeEffect* create( TargetType type, Property property, int *property_change);

	virtual void effect( Target& target );
private:
	virtual bool init( TargetType type, Property property,  int *property_change);
private:
	Property m_property;	//改变的属性
	int* m_property_change;	// 改变多少属性

};

#endif // !_POWER_CHANGE_EFFECT_H_