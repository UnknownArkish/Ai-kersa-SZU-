#include"StateEffect.h"

#include"StateHeader.h"

StateEffect* StateEffect::create(TargetType target_type, StateType state_type, std::string picPath, std::string name, std::string info, int rounds,
	bool isCanEffect, bool isTemporary, bool isCanOverlay, Property property, int* property_change) {

	StateEffect* pRet = new(std::nothrow)StateEffect();
	if (pRet && pRet->init(target_type, state_type, picPath, name, info, rounds, isCanEffect, isTemporary , isCanOverlay,property, property_change)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool StateEffect::init(
	TargetType target_type, StateType state_type, std::string picPath, std::string name, std::string info, int rounds, 
	bool isCanEffect, bool isTemporary, bool isCanOverlay, Property property, int* property_change) {

	if (!BaseEffect::init(target_type)) {
		return false;
	}

	m_state_type = state_type;
	m_picPath = picPath;
	m_name = name;
	m_info = info;
	m_continues_rouds = rounds;
	m_isCanEffect = isCanEffect;
	m_isTemporary = isTemporary;
	m_isCanOverlay = isCanOverlay;

	m_property = property;
	m_property_change = property_change;

	return true;
}

void StateEffect::effect(Target& target) {
	switch (m_type) {
		case TargetType::TO_PLAYER:
			for (Player* player : target.players) {
				switch (m_state_type) {
					case StateType::Property_Change:
						player->addState(PropertyChangeState::create(m_picPath, m_name, m_info, m_continues_rouds, m_isCanEffect, m_isTemporary, m_isCanOverlay , m_property, *m_property_change));
						break;

					//以下为一般状态的产生
					case StateType::Vulnerable :
					case StateType::Weak:
						player->addState(GeneralState::create(m_state_type, m_picPath, m_name, m_info, m_continues_rouds , m_isCanOverlay));
						break;
				}
			}
			break;

		case TargetType::TO_ENEMY:
			for (BaseEnemy* enemy : target.enemys) {
				switch (m_state_type) {
					case StateType::Property_Change:
						enemy->addState(PropertyChangeState::create(m_picPath, m_name, m_info, m_continues_rouds, m_isCanEffect, m_isTemporary, m_isCanOverlay, m_property, *m_property_change));
						break;

					//以下为一般状态的产生
					case StateType::Vulnerable:
					case StateType::Weak:
						enemy->addState(GeneralState::create(m_state_type, m_picPath, m_name, m_info, m_continues_rouds , m_isCanOverlay));
						break;
				}
			}

			break;
		case TargetType::TO_CARD_LAYER:
			break;
	}

}