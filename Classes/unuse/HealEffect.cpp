#include"HealEffect.h"

HealEffect* HealEffect::create( TargetType type ,  int health) {
	HealEffect* pRet = new(std::nothrow)HealEffect();
	if (pRet && pRet->init(type,  health)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool HealEffect::init(TargetType type, int health) {
	if (!BaseEffect::init(type)) {
		return false;
	}
	m_health = health;
	return true;
}

void HealEffect::effect( Target& target ) {
	switch (m_type) {
	case TargetType::TO_PLAYER:
		for (Player* player : target.players) {
			player->heal(m_health);
		}

		break;
	case TargetType::TO_ENEMY:
		for (BaseEnemy* enemy : target.enemys) {
			enemy->heal(m_health);
		}
		break;

	case TargetType::TO_CARD_LAYER:
		//ÔÝ¿Õ
		break;
	}
}
