#pragma once

#ifndef _BASE_BEHAVIOUR_H_
#define _BASE_BEHAVIOUR_H_

#include"GameConfig.h"
#include"BaseEffect.h"
#include"Target.h"

struct IntentType {
	bool isAttack;
	bool isDefend;
	bool isStengthen;
	bool isCurse;
};
struct BehaviourDigital {
	int damage_digital = 0;
	int armor_digital = 0;
};

//本质上是一个图标＋说明，也就是敌人头上的意图
//含有Vector<BaseEffect>，由AIManager来管理每个敌人持有的BaseBehaviour
class BaseBehaviour :public Node {
public:
	static BaseBehaviour* creaet();

	void updateIntent( std::string picPath );	//用以更新意图

	void addEffect(BaseEffect* effect) { m_effects.pushBack(effect); }	//添加Effect
	void effect( Target& target );	//驱动Behaviour的函数


	IntentType m_intent_tpye;	//点击时，根据这个产生意图信息
	TargetNeed m_target_need;	//用以产生Target
	BehaviourDigital m_behaviour_digital;	//用以存储该行为会造成的digital
	BehaviourDigital m_pre_digital;	//辅助更新digital
private:
	virtual bool init();
	virtual void update(float dt);

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
private:
	Sprite * m_icon_sprite;	//意图图标
	Label* m_tip_label;	//攻击/防御数值Label

	std::string info;	//意图说明

	Vector<BaseEffect*> m_effects;
};

#endif // !_BASE_BEHAVIOUR_H_