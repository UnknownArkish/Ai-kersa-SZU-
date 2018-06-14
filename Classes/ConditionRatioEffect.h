#pragma once

#ifndef _CONDITION_RATIO_EFFECT_H_
#define _CONDITION_RATIO_EFFECT_H_

#include"ConditionEffect.h"
#include"BaseEffect.h"

//条件比率Effect 
class ConditionRatioEffect :public BaseEffect {
public:
	//条件目标，条件枚举，满足方式，满足条件数值；结果枚举，结果目标，默认造成结果，满足条件造成结果
	static ConditionRatioEffect* create(
		TargetType condition_target, Property condition, Condition_Way condition_way, float ratio, TargetType result_target, Property result, int* defaultResult, int ratio_of_result);

	virtual void effect(Target& target);
private:
	virtual bool init(
		TargetType condition_target, Property condition, Condition_Way condition_way, float ratio, TargetType result_target, Property result, int* defaultResult, int ratio_ofresult);

	bool getFlag(BaseCharacter* character);
	void effect_(bool flag, Target& target);
	void effect_single(bool flag, BaseCharacter* character);

private:
	TargetType m_condition_target;	//条件目标
	Property m_condition;	//条件
	Condition_Way m_condition_way;
	float m_ratio;	//满足条件

	TargetType m_result_target;	//结果目标
	Property m_result;	//结果
	int* m_defaultResult;	//默认造成结果
	int m_ratio_of_result;	//满足条件造成结果

};


#endif // !_CONDITION_RATIO_EFFECT_H_
