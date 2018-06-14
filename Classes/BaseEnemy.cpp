#include"BaseEnemy.h"
#include"BaseBehaviour.h"

BaseEnemy::BaseEnemy() {

}
BaseEnemy::~BaseEnemy() {

}

BaseEnemy* BaseEnemy::create(std::string picPath, int max_hp, int armor, int power, int agility , EnemyType enemy_type) {
	BaseEnemy* pRet = new(std::nothrow)BaseEnemy();
	if (pRet && pRet->init(picPath, max_hp, armor, power, agility , enemy_type)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool BaseEnemy::init(std::string picPath, int max_hp, int armor, int power, int agility , EnemyType enemy_type) {
	if (!BaseCharacter::init(picPath, max_hp, true , armor, power, agility)) {
		return false;
	}
	m_enemy_type = enemy_type;

	switch (m_enemy_type) {
		case EnemyType::Demo_Enemy:
			this->m_behaviour_threshold = { 0.8f , 1.2f  };
			//this->m_behaviour_weight = { 1 , 1.2 , 1.2 , 0.8 , 0.8 , 
			//							1.2 , 1 , 0.6 , 1.0 , 1.4 };
			break;
	}

	auto m_behaviour = BaseBehaviour::creaet();
	m_behaviour->setPosition(0, this->getContentSize().height / 2 + 64);
	this->addChild(m_behaviour , 1 , "Intent");

	return true;
}