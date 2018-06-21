#include"AIManager.h"
#include"BaseBehaviour.h"
#include"EffectHeader.h"
#include"GameSceneDemo.h"

AIManager* AIManager::create(Player* player, Vector<BaseEnemy*> enemys) {
	AIManager* pRet = new(std::nothrow)AIManager();
	if (pRet && pRet->init(player, enemys)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool AIManager::init(Player* player, Vector<BaseEnemy*> enemys) {
	if (!Node::init()) {
		return false;
	}

	m_player = player;
	m_enemys = enemys;
	
	createIntent(1);	//产生Intent
	return true;
}

void AIManager::createIntent( int round ) {
	for (BaseEnemy* enemy : m_enemys) {
		switch (enemy->getEnemyType()) {
			case EnemyType::Demo_Enemy:	//打算是一种怪物设计一个AI方案
				BaseBehaviour * behaviour = ((BaseBehaviour*)enemy->getChildByName("Intent"));
				behaviour->m_behaviour_digital = { 0 , 0 };
				behaviour->m_pre_digital = behaviour->m_behaviour_digital;
				behaviour->m_target_need = { 0 , 0 , 0 };

				if (round == 1) {
					behaviour->m_target_need.enemy_need = 1;
					behaviour->m_intent_tpye = { false , false , true , false };
					behaviour->addEffect(StateEffect::create(TargetType::TO_ENEMY, StateType::Property_Change, "state/inner_strength.png", "", "", -1, true, false, true, Property::Power, new int(1)));
					continue;
				}
				else if( round % 2  ){
					behaviour->m_behaviour_digital = { 6 , 0 };
					behaviour->m_pre_digital = behaviour->m_behaviour_digital;
					behaviour->m_target_need = { 1 , 1 , 0 };
					behaviour->m_intent_tpye = { true , false , false , false };

					behaviour->addEffect(DamageEffect::create(TargetType::TO_PLAYER, &behaviour->m_behaviour_digital.damage_digital));
				}
				else {
					behaviour->m_behaviour_digital = { 4 , 3 };
					behaviour->m_pre_digital = behaviour->m_behaviour_digital;
					behaviour->m_target_need = { 1 , 1 , 0 };
					behaviour->m_intent_tpye = { true , true , false , false };

					behaviour->addEffect(DamageEffect::create(TargetType::TO_PLAYER, &behaviour->m_behaviour_digital.damage_digital));
					behaviour->addEffect(PropertyChangeEffect::create(TargetType::TO_ENEMY, Property::Armor , &behaviour->m_behaviour_digital.armor_digital));
				}
				break;

				//float attack_weight;
				//float defend_weight;
				//bool isAttack;
				//bool isDefend;

				//attack_weight = 128 * enemy->getMaxHP() / enemy->getHP() / 2.8f 
				//	* m_player->getMaxHP() / m_player->getHP() / 2.1f 
				//	* enemy->getPower() / 1.6;
				//if (attack_weight > 256)	attack_weight = 256;

				//defend_weight = 128 * enemy->getMaxHP() / enemy->getHP() / 3.0f
				//	* m_player->getHP() / m_player->getMaxHP() / 1.3f
				//	* enemy->getAgility() / 1.8;
				//if (defend_weight > 256)	defend_weight = 256;
				//attack_weight = attack_weight / 256 + 1;
				//defend_weight = defend_weight / 256 + 1;

				//if (attack_weight > enemy->m_behaviour_threshold.attack_threshold) {
				//	isAttack = true;
				//	behaviour->m_behaviour_digital.damage_digital = 10;
				//	behaviour->m_pre_digital = behaviour->m_behaviour_digital;

				//	behaviour->m_target_need.player_need = 1;
				//	behaviour->addEffect(DamageEffect::create(TargetType::TO_PLAYER, &behaviour->m_behaviour_digital.damage_digital));
				//}
				//if (defend_weight > enemy->m_behaviour_threshold.defend_threshold) {
				//	isDefend = true;

				//	behaviour->m_behaviour_digital.armor_digital = 6;
				//	behaviour->m_pre_digital = behaviour->m_behaviour_digital;

				//	behaviour->m_target_need.enemy_need = 1;
				//	behaviour->addEffect(PropertyChangeEffect::create(TargetType::TO_ENEMY, Property::Armor , &behaviour->m_behaviour_digital.armor_digital));
				//}
				////默认行为
				//if (!isAttack && !isDefend) {
				//	behaviour->m_behaviour_digital.damage_digital = 10;
				//	behaviour->m_pre_digital = behaviour->m_behaviour_digital;

				//	behaviour->m_target_need.player_need = 1;
				//	behaviour->addEffect(DamageEffect::create(TargetType::TO_PLAYER, &behaviour->m_behaviour_digital.damage_digital));
				//}
				//break;
				//	//获取意图，并修改意图
				//	behaviour->m_behaviour_digital = { 5 , 0 };
				//	behaviour->m_pre_digital = behaviour->m_behaviour_digital;
				//	behaviour->m_target_need = { 1 , 1 , 0 };
				//	behaviour->m_intent_tpye = { true , false , false , false };

				//	behaviour->addEffect(DamageEffect::create(TargetType::TO_PLAYER, &behaviour->m_behaviour_digital.damage_digital));
				//	break;
		}
	}
}
void AIManager::effect_when_round_end( int round ) {
	for (BaseEnemy* enemy : m_enemys) {
		enemy->effect_when_round_end();	//更新敌人状态

		if (!enemy->isDead()) {
			BaseBehaviour* behaviour = ((BaseBehaviour*)enemy->getChildByName("Intent"));
			Target target = ((GameSceneDemo*)this->getParent())->getTarget(behaviour);
			behaviour->effect(target);
		}
	}
	createIntent( round );
}