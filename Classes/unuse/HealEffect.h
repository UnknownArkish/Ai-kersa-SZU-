#pragma once

#ifndef _HEAL_EFFECT_H_
#define _HEAL_EFFECT_H_

#include"BaseEffect.h"
class HealEffect :public BaseEffect {
public:
	static HealEffect* create( TargetType type , int health);
	virtual void effect(Target& target);
private:
	virtual bool init( TargetType type,  int health);
private:
	int m_health;
};

#endif // !_HEAL_EFFECT_H_
