#pragma once

#ifndef _BASE_STATE_H_
#define _BASE_STATE_H_

#include"GameConfig.h"

//暂时利用枚举类型来表示所有的状态
enum StateType {
	Weak = 0,	//虚弱
	Vulnerable,	//易伤
	Ghost,	//幽灵化
	Property_Change	//改变力量的状态
};

//所有状态类的基类，用于附在人物和敌人身上
//本质上是一个图标，类成员有名字，持续回合数
class BaseState :public Node {
public:
	//状态类型、图标路径、状态名字、状态信息、持续回合、回合结束时是否可以作用、是否为暂时状态、是否可以叠加
	bool init( StateType type, std::string picPath , std::string name , std::string info , int rounds , bool isCanEffect , bool isTemporary , bool isCanOverlay );

	virtual void effect() = 0;	//每回合结束调用的函数
	virtual void effect_when_end() = 0;	//持续回合结束后调用的函数，一般是从父节点中去除和删除状态

	void changeContinuesRound(int rounds) { m_left_rounds += rounds; m_continues_rounds += rounds; updateRoundsLabel(); }

	std::string getName() { return m_name; }
	int getContinuesRound() { return m_continues_rounds; }
	bool isCanOverLay() { return m_isCanOverLay; }

	StateType getStateType() { return m_type; }
private:

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

protected:
	void updateRoundsLabel() {
		m_continues_rouds_label->setString(Value(m_left_rounds).asString());
	}

protected:
	StateType m_type;	//表示状态ID值

	Sprite * m_icon_sprite;	//图标精灵
	Label* m_continues_rouds_label;	//持续回合Label

	std::string m_name;	//状态名字
	std::string m_info;	//状态信息
	int m_continues_rounds;	//持续回合，-1为永久
	int m_left_rounds;	//剩余回合数

	bool m_isCanEffect;	//每回合结束是否能作用，用以表示回合结束增益的状态，如每回合提高若干点力量等
	bool m_isTemporary;	//持续回合结束后是否需要还原回施加状态前，如暂时获得3点力量2回合
	bool m_isCanOverLay;	//是否可以叠加状态
};

#endif // !_BASE_STATE_H_