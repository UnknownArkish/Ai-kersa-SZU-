#pragma once

#ifndef _PROPERTY_CHANGE_STATE_H_
#define _PROPERTY_CHANGE_STATE_H_

#include"BaseState.h"
#include"BaseCharacter.h"
#include"Player.h"

//一个Demo样式的State，可以仿照这个写出各种各样的State
class PropertyChangeState : public BaseState {
public:
	//状态精灵路径、状态名字、状态信息、持续回合数、每回合是否能作用、是否为暂时状态、是否可以叠加、改变哪个属性、属性改变值
	static PropertyChangeState* create(
		std::string picPath, std::string name, std::string info , int rounds, bool isCanEffect , bool isTemporary, bool isCanOverlay, Property property ,  int property_change );

	virtual void effect();
	virtual void effect_when_end();
private:
	bool init(std::string picPath, std::string name, std::string info , int rounds, bool isCanEffect , bool isTemporary, bool isCanOverlay, Property property, int property_change);
private:
	Property m_property;
	int m_property_change;
};

#endif // !_POWER_UP_STATE_
