#pragma once

#ifndef _BASE_ENEMY_H_
#define _BASE_ENEMY_H_

enum EnemyType {
	Demo_Enemy
};

//敌人行为阈值
struct BehaviourThreshold {
	float attack_threshold;
	float defend_threshold;
	//float strengthen_threashold;
	//float curse_threashold;
};


#include"BaseCharacter.h"

class BaseEnemy :public BaseCharacter {
public:
	static BaseEnemy* create(std::string picPath, int max_hp, int armor, int power, int agility , EnemyType enemy_type );

	EnemyType getEnemyType() { return m_enemy_type; }

	BehaviourThreshold m_behaviour_threshold;
	//BehaviourWeight m_behaviour_weight;
private:
	BaseEnemy();
	~BaseEnemy();

	virtual bool init(std::string picPath, int max_hp, int armor, int power, int agility , EnemyType enemy_type);
private:
	EnemyType m_enemy_type;
	//BaseBehaviour * m_behaviour;
};


#endif // !_BASE_ENEMY_H_
