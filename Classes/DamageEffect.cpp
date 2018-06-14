#include"DamageEffect.h"

DamageEffect* DamageEffect::create( TargetType type , int* damage) {
	DamageEffect* pRet = new(std::nothrow)DamageEffect();
	if (pRet && pRet->init(type, damage , 1 , false)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
DamageEffect* DamageEffect::create(TargetType type, int* damage, int count) {
	DamageEffect* pRet = new(std::nothrow)DamageEffect();
	if (pRet && pRet->init(type, damage , count , false)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
DamageEffect* DamageEffect::create(TargetType type, int* damage, int count , bool is_target_random) {
	DamageEffect* pRet = new(std::nothrow)DamageEffect();
	if (pRet && pRet->init(type, damage, count, is_target_random)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool DamageEffect::init( TargetType type , int* damage , int count , bool is_taget_random) {
	if (!BaseEffect::init(type)) {
		return false;
	}
	m_damage = damage;
	m_count = count;
	m_is_target_random = is_taget_random;

	return true;
}

void DamageEffect::effect( Target& target ) {
	switch (m_type) {
	case TargetType::TO_PLAYER:
		if (m_is_target_random) {
			for (int i = 0; i < m_count; i++) {
				BaseCharacter* character = target.players.at( (random() + 13 ) * i * 57 % target.players.size());
				character->hurt(*m_damage);
			}
		}
		else {
			for (Player* player : target.players) {
				for (int i = 0; i < m_count; i++) {
					player->hurt(*m_damage);
				}
			}
		}

		break;
	case TargetType::TO_ENEMY:
		if (m_is_target_random) {
			for (int i = 0; i < m_count; i++) {
				BaseCharacter* character = target.enemys.at(random() * i * 57 % target.enemys.size());
				character->hurt(*m_damage);
			}
		}
		else {
			for (BaseEnemy* enemy : target.enemys) {
				for (int i = 0; i < m_count; i++) {
					enemy->hurt(*m_damage);
				}
			}
		}
		break;

	case TargetType::TO_CARD_LAYER:
		//ÔÝ¿Õ
		break;
	}
}