#include"ArmorEffect.h"

ArmorEffect* ArmorEffect::create(TargetType type, int* armor) {
	ArmorEffect* pRet = new(std::nothrow)ArmorEffect();
	if (pRet && pRet->init(type,  armor)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool ArmorEffect::init(TargetType type, int* armor) {
	if (!BaseEffect::init(type)) {
		return false;
	}
	m_armor = armor;
	return true;
}

void ArmorEffect::effect( Target& target ) {
	switch(m_type){
		case TargetType::TO_PLAYER:
			for (Player* player : target.players) {
				player->changeArmor(*m_armor);
			}

			break;
		case TargetType::TO_ENEMY:
			for (BaseEnemy* enemy : target.enemys) {
				enemy->changeArmor(*m_armor);
			}
			break;

		case TargetType::TO_CARD_LAYER:
			//ÔÝ¿Õ
			break;
	}
}