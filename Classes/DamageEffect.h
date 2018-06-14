#pragma once

#ifndef _DAMAGE_EFFECT_H_
#define _DAMAGE_EFFECT_H_

#include"BaseEffect.h"

//一个Demo样例的Effect子类，可仿照这个写出各种各样的Effect
//该类是造成伤害效果
class DamageEffect :public BaseEffect {
public:
	static DamageEffect* create(TargetType type, int* damage);
	static DamageEffect* create(TargetType type, int* damage, int count);
	static DamageEffect* create( TargetType type ,  int* damage , int count , bool is_target_random );

	//Override
	virtual void effect( Target& target);
private:
	virtual bool init( TargetType type , int* damage , int count , bool is_target_random);

private:
	int* m_damage;
	int m_count;
	bool m_is_target_random;
};


#endif // !_DAMAGE_EFFECT_H_
