#include"ConditionRatioEffect.h"

ConditionRatioEffect* ConditionRatioEffect::create(
	TargetType condition_target, Property condition, Condition_Way condition_way, float ratio, TargetType result_target, Property result, int *defaultResult, int ratio_of_result) {

	ConditionRatioEffect* pRet = new(std::nothrow)ConditionRatioEffect();
	if (pRet&& pRet->init(condition_target, condition, condition_way, ratio, result_target, result, defaultResult, ratio_of_result)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool ConditionRatioEffect::init(
	TargetType condition_target, Property condition, Condition_Way condition_way, float ratio, TargetType result_target, Property result, int* defaultResult, int ratio_of_result) {

	if (!BaseEffect::init(condition_target)) {	//这里传的TO_PLAYER并无实际作用
		return false;
	}
	m_condition_target = condition_target;
	m_condition = condition;
	m_condition_way = condition_way;
	m_ratio = ratio;

	m_result = result;
	m_result_target = result_target;
	m_defaultResult = defaultResult;
	m_ratio_of_result = ratio_of_result;
	return true;
}

//比率条件Effect目前只有最大生命值
bool ConditionRatioEffect::getFlag(BaseCharacter* character) {
	switch (m_condition) {
	case Property::Health:
		switch (m_condition_way) {
		case Condition_Way::Greater_Equal:
			return character->getHP() >= character->getMaxHP() * m_ratio ? true : false;
			break;
		case Condition_Way::Greater:
			return character->getHP() > character->getMaxHP() * m_ratio ? true : false;
			break;
		case Condition_Way::Equal:
			return character->getHP() == character->getMaxHP() * m_ratio ? true : false;
			break;
		case Condition_Way::Less:
			return character->getHP() < character->getMaxHP() * m_ratio ? true : false;
			break;
		case Condition_Way::Less_Equal:
			return character->getHP() <= character->getMaxHP() * m_ratio ? true : false;
			break;
		}
		break;
	}
}

void ConditionRatioEffect::effect(Target& target) {
	switch (m_condition_target) {
	case TargetType::TO_PLAYER:
		for (Player* player : target.players) {
			bool flag = getFlag(player);	//获得条件
			effect_(flag, target);
		}
		break;
	case TargetType::TO_ENEMY:
		for (BaseEnemy* enemy : target.enemys) {
			bool flag = getFlag(enemy);	//获取条件
			if (m_result_target == TargetType::TO_ENEMY) {
				effect_single(flag, enemy);	//为了防止对每个敌人都用同一个Flag而造成多次伤害
			}
			else {
				effect_(flag, target);
			}
		}
	}
}

void ConditionRatioEffect::effect_(bool flag, Target& target) {
	switch (m_result_target) {
	case TargetType::TO_PLAYER:
		for (Player* player : target.players) {
			switch (m_result) {
			case Property::Health:
				if (*m_defaultResult > 0) {
					player->heal(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
				}
				else if (*m_defaultResult < 0) {
					player->hurt(flag ? -(m_ratio_of_result * (*m_defaultResult)) : -*m_defaultResult);
				}
				break;
			case Property::Armor:
				player->changeArmor(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
				break;
			case Property::Power:
				player->changePower(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
				break;
			case Property::Agility:
				player->changeAgility(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
				break;
			case Property::Magic:
				player->changeMagic(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
				break;
			}
		}
		break;
	case TargetType::TO_ENEMY:
		for (BaseEnemy* enemy : target.enemys) {
			switch (m_result) {
			case Property::Health:
				if (*m_defaultResult > 0) {
					enemy->heal(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
				}
				else if (*m_defaultResult < 0) {
					enemy->hurt(flag ? -(m_ratio_of_result * (*m_defaultResult)) : -*m_defaultResult);
				}
				break;
			case Property::Armor:
				enemy->changeArmor(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
				break;
			case Property::Power:
				enemy->changePower(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
				break;
			case Property::Agility:
				enemy->changeAgility(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
				break;
			}
		}
		break;
	}
}
void ConditionRatioEffect::effect_single(bool flag, BaseCharacter* charcter) {
	switch (m_result) {
	case Property::Health:
		if (*m_defaultResult > 0) {
			charcter->heal(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
		}
		else if (*m_defaultResult < 0) {
			charcter->hurt(flag ? -(m_ratio_of_result * (*m_defaultResult)) : -*m_defaultResult);
		}
		break;
	case Property::Armor:
		charcter->changeArmor(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
		break;
	case Property::Power:
		charcter->changePower(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
		break;
	case Property::Agility:
		charcter->changeAgility(flag ? (m_ratio_of_result * (*m_defaultResult)) : *m_defaultResult);
		break;
	}
}