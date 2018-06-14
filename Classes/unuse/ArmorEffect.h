#pragma once

#ifndef _ARMOR_EFFECT_H_
#define _ARMOR_EFFECT_H_

#include"BaseEffect.h"

class ArmorEffect :public BaseEffect {
public:
	static ArmorEffect* create( TargetType type , int* armor);

	virtual void effect( Target& target );
private:
	virtual bool init(TargetType type, int* armor);

private:
	int* m_armor;
};

#endif // !_ARMOR_EFFECT_H_
