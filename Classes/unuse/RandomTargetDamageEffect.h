#pragma once

#ifndef _RANDOM_TARGET_DAMAGE_EFFECT_H_
#define _RANDOM_TARGET_DAMAGE_EFFECT_H_

#include"GameConfig.h"
#include"BaseEffect.h"

class RandomTargetDamageEffect :public BaseEffect {
public:
	static RandomTargetDamageEffect* create(TargetType type, int *damage, int count);

	virtual void effect(Target& target);
private:
	virtual bool init( TargetType type , int* damage , int count );
private:
	int* m_damage;
	int m_count;
};

#endif // !_RANDOM_TARGET_DAMAGE_EFFECT_H_