#pragma once

#ifndef _DRAW_CARD_EFFECT_H_
#define _DRAW_CARD_EFFECT_H_

#include"BaseEffect.h"

enum DrawFrom{
	From_Card_Library,
	From_Dis_Library
};

class DrawCardEffect : public BaseEffect {
public:
	static DrawCardEffect * create( TargetType type , int draw_num , DrawFrom from );

	virtual void effect(Target& target);
private:
	virtual bool init( TargetType type , int draw_num, DrawFrom from);
private:
	int m_draw_num;	//³éÅÆÕÅÊý
					//-1Îª³éÂú
	DrawFrom m_from;
};


#endif // !_DRAW_CARD_EFFECT_H_