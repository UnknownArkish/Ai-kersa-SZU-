#pragma once

#ifndef _BASE_EFFECT_H_
#define _BASE_EFFECT_H_

#include"GameConfig.h"
#include"Target.h"


//所有Effect的基类，主要附在卡牌上面
//可以继承自这个类并添加自己的成员之后可以造成各种各样的效果，其中effect()为纯虚驱动函数
//可参照DamageEffect
class BaseEffect:public Node {
public:
	//纯虚函数effect，传参为玩家和敌人的基类BaseCharacter，可根据实际需要强制转换类型
	virtual void effect(  Target& target ) = 0;
	virtual bool init( TargetType type  );
protected:
	TargetType m_type;	//该Effect是否针对敌人
};


#endif // !_BASE_EFFECT_H_

