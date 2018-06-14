#include"PropertyChangeEffect.h"

PropertyChangeEffect* PropertyChangeEffect::create( TargetType type, Property property , int* property_change) {
	PropertyChangeEffect* pRet = new(std::nothrow)PropertyChangeEffect();
	if (pRet && pRet->init(  type , property , property_change )) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool PropertyChangeEffect::init( TargetType type, Property property, int* property_change) {
	if (!BaseEffect::init( type )) {
		return false;
	}
	m_property = property;
	m_property_change = property_change;
	return true;
}

void PropertyChangeEffect::effect( Target& target ) {
	switch (m_type) {
		case TargetType::TO_PLAYER: {//对玩家
			for (Player* player : target.players) {
				switch (m_property) {
					case Property::Health:
						if (m_property_change > 0) {
							player->heal(*m_property_change);
						}
						else if(m_property_change < 0){
							player->hurt(-*m_property_change);
						}
						break;
					case Property::Armor:
						if (*m_property_change == 0) {
							player->changeArmor( player->getArmor() );
						}
						else {
							player->changeArmor(*m_property_change);
						}
						break;

					case Property::Power:
						if ( *m_property_change == 0) {
							player->changePower( player->getPower() );
						}
						else {
							player->changePower(*m_property_change);
						}
						break;

					case Property::Agility:
						if (*m_property_change == 0) {
							player->changeAgility( player->getAgility() );
						}
						else {
							player->changeAgility(*m_property_change);
						}
						break;

					case Property::Magic:
						if (*m_property_change == 0) {
							player->changeMagic( player->getMagic() );
						}
						else {
							player->changeMagic(*m_property_change);
						}
						break;

					case Property::Cost:
						if (*m_property_change == 0) {
							player->changeCost( player->getCost() );
						}
						else {
							player->changeCost(*m_property_change);
						}
						break;
				}
			}
			break;
		}
		case TargetType::TO_ENEMY: {	//对敌人
			for (BaseEnemy* enemy : target.enemys) {
				switch (m_property) {
					case Property::Health:
						if (m_property_change > 0) {
							enemy->heal(*m_property_change);
						}
						else if (m_property_change < 0) {
							enemy->hurt(-*m_property_change);
						}
						break;

					case Property::Armor:
						if (*m_property_change == 0) {
							enemy->changeArmor(enemy->getArmor());
						}
						else {
							enemy->changeArmor(*m_property_change);
						}
						break;

					case Property::Power:
						if (*m_property_change == 0) {
							enemy->changePower(enemy->getPower());
						}
						else {
							enemy->changePower(*m_property_change);
						}
						break;

					case Property::Agility:
						if (*m_property_change == 0) {
							enemy->changeAgility(enemy->getAgility());
						}
						else {
							enemy->changeAgility(*m_property_change);
						}
						break;
					}
			}
			break;
		}
	}

	//for each (BaseCharacter* character in characters)
	//{
	//	if (m_isToEnemy && character->isEnemy()) {
	//		//如果持续回合为1并且不是暂时增加属性则直接修改属性值
	//		if (m_continues_rouds == 1 && !m_isTemporary ) {
	//			switch (m_property) {
	//			case Property::Health:
	//				if (m_property_change > 0) {
	//					character->heal(m_property_change);
	//				}
	//				else if (m_property_change < 0) {
	//					character->hurt(-m_property_change);
	//				}
	//				break;

	//			case Property::Armor:
	//				character->changeArmor(m_property_change);
	//				break;

	//				case Property::Power:
	//					character->changePower(m_property_change);
	//					break;

	//				case Property::Agility:
	//					character->changeAgility(m_property_change);
	//					break;
	//			}
	//		}
	//		else {	
	//			//否则添加对应的改变属性的状态，其中前两个参数为状态图标路径和状态名字
	//			character->addState(
	//				PropertyChangeState::create(
	//					m_picPath, m_name, m_info , m_continues_rouds,  m_isCanEffect , m_isTemporary ,m_property,  m_property_change));
	//		}
	//	}
	//	//如果是对玩家则还要考虑智力
	//	else if( !m_isToEnemy && !character->isEnemy() ){
	//		if (m_continues_rouds == 1 && !m_isTemporary) {
	//			switch (m_property) {
	//				case Property::Health:
	//					if (m_property_change > 0) {
	//						character->heal(m_property_change);
	//					}
	//					else if (m_property_change < 0) {
	//						character->hurt(-m_property_change);
	//					}
	//					break;

	//				case Property::Armor:
	//					character->changeArmor(m_property_change);
	//					break;

	//				case Property::Power:
	//					character->changePower(m_property_change);
	//					break;

	//				case Property::Agility:
	//					character->changeAgility(m_property_change);
	//					break;

	//				case Property::Magic:
	//					((Player*)character)->changeMagic(m_property_change);
	//					break;

	//				case Property::Cost:
	//					((Player*)character)->changeCost(m_property_change);
	//					break;
	//			}
	//		}
	//		else {
	//			character->addState(
	//				PropertyChangeState::create(
	//					m_picPath, m_name, m_info , m_continues_rouds, m_isCanEffect , m_isTemporary ,m_property, m_property_change));
	//		}
	//		break;
	//	}
	//}
}