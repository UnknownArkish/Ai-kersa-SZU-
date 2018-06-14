#pragma once

#ifndef _BASE_CHARACTER_H_
#define _BASE_CHARACTER_H_

#include"GameConfig.h"
#include"BaseState.h"

#define STATE_NUM_PER_ROW 5	//每行最多放六个状态

enum Property {
	Health,
	Armor,

	Power,
	Agility,
	Magic,

	Cost
};
struct CharacterState {
	bool is_weak;
	bool is_vulnerable;
};

class BaseCharacter :public Node {
public:
	BaseCharacter();
	~BaseCharacter();

	//贴图路径、最大HP、护甲、力量、敏捷
	virtual bool init( std::string picPath, int max_hp , bool isEnemy , int armor , int power, int agility );
	
	//伤害、治疗
	void hurt(int damage);
	void heal(int health);

	//改变最大生命值
	void changeMaxHP(int max_hp);
	//改变护甲值
	void changeArmor(int armor);

	//改变力量、敏捷、智力值
	void changePower(int power);
	void changeAgility(int agility);

	void addState(BaseState* state );
	void removeState(BaseState* state);
	void toEffectState();	//回合结束后调用，用以驱动State的effect

	int getHP() { return m_hp; }	//获得生命值
	int getMaxHP() { return m_max_hp; }	//获得最大生命值
	int getArmor() { return m_Armor; }	//护甲值
	int getPower() { return m_Power; }	//力量值
	int getAgility() { return m_Agility; }	//敏捷值

	bool isHaveArmor() { return m_isHaveArmor; }	//是否有护甲值
	bool isHavePower() { return m_isHavePower; }	//是否有力量值
	bool isHaveAgility() { return m_isHaveAgility; }	//是否有敏捷值

	void effect_when_round_end();	//回合结束之后调用的函数

	bool isEnemy() { return m_isEnemy; }

	virtual Size getContentSize() { return m_sprite->getContentSize(); }	//override
	virtual Rect getBoundingBox() { 
		Rect rect = Rect(
			this->getPositionX() - getContentSize().width / 2 , this->getPositionY() - getContentSize().height /2 , 
			getContentSize().width, getContentSize().height);
		return rect; 
	}	//overide
private:
	//更新HP_Label
	void updateHPLabel();

	void updateStateLayout();
protected:
	int m_hp;	//生命值
	int m_max_hp;	//最大生命值

	int m_Armor;	//当前护甲
	int m_Power;	//当前力量
	int m_Agility;	//当前敏捷

	bool m_isDead;
	bool m_isEnemy;	//是否为敌人

	bool m_isHaveArmor;	//是否有护甲
	bool m_isHavePower;	//是否有力量
	bool m_isHaveAgility;	//敏捷

	Sprite* m_sprite;	//人物贴图
	Label* m_hp_label;	//生命值Label

	Vector<BaseState*> m_state_vector;

	//先暂时用Label表示护甲、力量、敏捷，后面可能以图标的形式表现，并放在一个Layer当中
	Label* m_armor_label;
	Label* m_power_label;
	Label* m_agility_label;
};

#endif // !_BASE_CHARACTER_H_
