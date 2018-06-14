#include"RandomTargetDamageEffect.h"

RandomTargetDamageEffect* RandomTargetDamageEffect::create(TargetType type, int* damage, int count) {
	RandomTargetDamageEffect* pRet = new(std::nothrow)RandomTargetDamageEffect();
	if (pRet && pRet->init(type, damage, count)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool RandomTargetDamageEffect::init(TargetType type, int* damage, int count) {
	if (!BaseEffect::init(type)) {
		return false;
	}

	m_damage = damage;
	m_count = count;

	return true;
}

void RandomTargetDamageEffect::effect(Target& target) {
	switch (m_type) {
		case TargetType::TO_PLAYER:
			for (int i = 0; i < m_count; i++) {
				BaseCharacter* character = target.players.at(random() * i * 57 % target.players.size());
				character->hurt(*m_damage);
			}
			break;
		case TargetType::TO_ENEMY:
			for (int i = 0; i < m_count; i++) {
				BaseCharacter* character = target.enemys.at( random() * i * 57 % target.enemys.size());
				character->hurt(*m_damage);
			}
			break;
	}
}