#pragma once

#ifndef _CONDITION_EFFECT_H_
#define _CONDITION_EFFECT_H_

#include"BaseEffect.h"

////条件枚举
//enum Condition{
//	If_Health,
//	If_Armor
//};
//大于等于、大于、等于、小于等于、小于
enum Condition_Way {
	Greater_Equal,
	Greater,
	Equal,
	Less_Equal,
	Less
};
////结果枚举
//enum Result {
//	Then_Damage,
//	Then_Armor,
//	Then_Heal
//};

//条件Effect 
class ConditionEffect:public BaseEffect {
public:
	//条件目标，条件枚举，满足方式，满足条件数值；结果枚举，结果目标，默认造成结果，满足条件造成结果
	static ConditionEffect* create(
		TargetType condition_target, Property condition, Condition_Way condition_way,  int defaultCondition, TargetType result_target, Property result,  int* defaultResult, int ratio_of_result);

	virtual void effect( Target& target );
private:
	virtual bool init(
		TargetType condition_target, Property condition, Condition_Way condition_way, int defaultCondition, TargetType result_target, Property result,  int* defaultResult, int ratio_of_result);

	bool getFlag(BaseCharacter* character);
	void effect_( bool flag , Target& target );
	void effect_single(bool flag, BaseCharacter* character);

private:
	TargetType m_condition_target;	//条件目标
	Property m_condition;	//条件
	Condition_Way m_condition_way;
	int m_defaultCondition;	//满足条件

	TargetType m_result_target;	//结果目标
	Property m_result;	//结果
	int* m_defaultResult;	//默认造成结果
	int m_ratio_of_result;	//满足条件造成结果

};



#endif // !_CONDITION_EFFECT_H_