#include"BaseBehaviour.h"

BaseBehaviour* BaseBehaviour::creaet() {
	BaseBehaviour* pRet = new(std::nothrow)BaseBehaviour();
	if (pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool BaseBehaviour::init() {
	if (!Node::init()) {
		return false;
	}

	m_icon_sprite = Sprite::create();
	this->addChild(m_icon_sprite);

	m_tip_label = Label::create("", "Arical", 20);
	this->addChild(m_tip_label);

	this->scheduleUpdate();
	return true;
}

void BaseBehaviour::update(float dt) {
	//这是用来更新Behaviour的伤害和护甲数值，它会根据父节点即敌人的力量和护甲而改变
	if (this->getParent()) {
		BaseEnemy* parent = (BaseEnemy*)(this->getParent());
		if ( m_behaviour_digital.damage_digital != 0 && parent->getPower() + m_pre_digital.damage_digital != m_behaviour_digital.damage_digital) {
			m_behaviour_digital.damage_digital = parent->getPower() + m_pre_digital.damage_digital;
		}
		if (m_behaviour_digital.armor_digital != 0 &&  parent->getAgility() + m_pre_digital.armor_digital != m_behaviour_digital.armor_digital) {
			m_behaviour_digital.armor_digital = parent->getAgility() + m_pre_digital.armor_digital;
		}

		__String *cache;
		if (m_behaviour_digital.damage_digital == 0 && m_behaviour_digital.armor_digital == 0) {
			cache = __String::create("");
		}
		else if (m_behaviour_digital.damage_digital == 0) {
			cache = __String::create("0 / " + Value(m_behaviour_digital.armor_digital).asString());
		}
		else if (m_behaviour_digital.armor_digital == 0) {
			cache = __String::create(Value(m_behaviour_digital.damage_digital).asString() + " / 0");
		}
		else {
			cache = __String::create(Value(m_behaviour_digital.damage_digital).asString() + " / " + Value(m_behaviour_digital.armor_digital).asString());
		}
		m_tip_label->setString(cache->getCString());
	}
}

void BaseBehaviour::updateIntent(std::string picPath) {
	auto sprite = Sprite::create(picPath);
	m_icon_sprite->setTexture(sprite->getTexture());
}

void BaseBehaviour::effect( Target& target ) {
	for (BaseEffect* effect : m_effects) {
		effect->effect(target);
	}
	m_effects.clear();
}


bool BaseBehaviour::onTouchBegan(Touch* pTouch, Event* pEvent) {
	return false;
}
void BaseBehaviour::onTouchEnded(Touch* pTouch, Event* pEvent) {

}