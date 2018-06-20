#include"BaseCharacter.h"

BaseCharacter::BaseCharacter() {
	m_hp = 0;
	m_max_hp = 0;

	//初始化赋值
	m_Armor = 0;
	m_Power = 0;
	m_Agility = 0;

	m_isDead = false;

	m_isHaveArmor = false;
	m_isHavePower = false;
	m_isHaveAgility = false;
}
BaseCharacter::~BaseCharacter() {

}

bool BaseCharacter::init(std::string picPath, int max_hp, bool isEnemy , int armor, int power, int agility) {
	if (!Node::init()) {
		return false;
	}
	Size visibleSize = _director->getVisibleSize();

	m_isEnemy = isEnemy;

	Size character_size = m_isEnemy ? game_enemy_size : game_player_size;

	//初始化人物精灵
	m_sprite = Sprite::create(picPath);
	float xScale = visibleSize.width * character_size.width / m_sprite->getContentSize().width;
	float yScale = visibleSize.height * character_size.height / m_sprite->getContentSize().height;
	m_sprite->setScale(xScale < yScale ? xScale : yScale);
	m_sprite->setPosition(0, 0);
	this->addChild(m_sprite, 5);

	//初始化HP_Label
	m_hp_label = Label::create("0 /0", "Arical", 16);
	m_hp_label->setColor(Color3B::BLACK);
	m_hp_label->setPosition(0, -m_sprite->getContentSize().height * m_sprite->getScale() / 2 - 10);
	this->addChild(m_hp_label, 3);

	//初始化护甲Label
	m_armor_label = Label::create("Armor: 0", "Arical", 20);
	m_armor_label->setColor(Color3B::BLACK);
	m_armor_label->setPosition(0, m_sprite->getContentSize().height * m_sprite->getScale() / 2 + 20);
	this->addChild(m_armor_label, 3);

	//初始化力量、敏捷、智力Label
	m_power_label = Label::create("Power: 0", "Arical", 16);
	m_power_label->setColor(Color3B::BLACK);
	m_power_label->setAnchorPoint(Vec2(1.0, 0.5));
	m_power_label->setPosition(
		-m_sprite->getContentSize().width* m_sprite->getScale() / 2 - m_power_label->getContentSize().width / 2 - 2, 0);
	this->addChild(m_power_label, 3);

	m_agility_label = Label::create("Agility: 0", "Arical", 16);
	m_agility_label->setColor(Color3B::BLACK);
	m_agility_label->setAnchorPoint(Point(1.0, 0.5));
	m_agility_label->setPosition(
		-m_sprite->getContentSize().width * m_sprite->getScale() / 2 - m_power_label->getContentSize().width / 2 - 2, m_power_label->getPositionY() - m_power_label->getContentSize().height);
	this->addChild(m_agility_label, 3);

	this->changeMaxHP(max_hp);
	this->changeArmor(armor);
	this->changePower(power);
	this->changeAgility(agility);

	return true;
}

void BaseCharacter::hurt(int damage) {
	if (m_isHaveArmor) {	//如果有护甲值
		if (damage > m_Armor) {
			damage = damage - m_Armor;
			m_Armor = 0;
		}
		else {
			m_Armor -= damage;
			damage = 0;
		}

		if (m_Armor == 0) {
			m_isHaveArmor = false;
		}
	}
	m_hp -= damage;
	if (m_hp <= 0) {
		m_isDead = true;
		m_hp = 0;
	}

	updateHPLabel();
	changeArmor(0);	//为了更新Armor
}
void BaseCharacter::heal(int health) {
	m_hp += health;
	if (m_hp > m_max_hp) {
		m_hp = m_max_hp;
	}
	updateHPLabel();
}

void BaseCharacter::changeMaxHP(int max_hp) {
	//如果改变的最大生命值大于现在的，则需要补差值
	if (max_hp > m_max_hp) {
		m_hp += (max_hp - m_max_hp);
	}
	//如果改变的最大生命值小于现在同时小于当前生命值，则把当前生命设为改变后的数值
	else if (max_hp < m_max_hp && max_hp < m_hp) {
		m_hp = max_hp;
	}
	m_max_hp = max_hp;

	updateHPLabel();
}

void BaseCharacter::changeArmor(int armor) {
	m_Armor += armor;
	if (m_Armor < 0) {
		m_Armor = 0;
	}

	m_isHaveArmor = m_Armor > 0 ? true : false;
	m_armor_label->setString("Armor: " + Value(m_Armor).asString());
}
void BaseCharacter::changePower(int power) {
	m_Power += power;
	if( !m_isEnemy )
		__NotificationCenter::getInstance()->postNotification(MSG_PLAYER_PROPERTY_CHANGE, this);

	m_isHavePower = m_Power != 0 ? true : false;
	m_power_label->setString("Power: " + Value(m_Power).asString());
}
void BaseCharacter::changeAgility(int agility) {
	m_Agility += agility;
	if (!m_isEnemy)
		__NotificationCenter::getInstance()->postNotification(MSG_PLAYER_PROPERTY_CHANGE, this);

	m_isHaveAgility = m_Agility != 0 ? true : false;
	m_agility_label->setString("Agility: " + Value(m_Agility).asString());
}

void BaseCharacter::toEffectState() {
	for (int i = m_state_vector.size() - 1; i >= 0; i--) {
		auto state = m_state_vector.at(i);
		state->effect();
	}
	//for (BaseState* state : m_state_vector) {
	//	state->effect();
	//}
	updateStateLayout();
}

void BaseCharacter::addState(BaseState* state) {
	for (BaseState* m_state : m_state_vector) {
		if (m_state->getName() == state->getName()) {
			if (m_state->isCanOverLay()) {
				m_state->changeContinuesRound(state->getContinuesRound());
				return;
			}
		}
	}

	m_state_vector.pushBack(state);

	updateStateLayout();
	state->setAnchorPoint(Point(0, 1.0));
	this->addChild(state);
}
void BaseCharacter::removeState(BaseState* state) {
	m_state_vector.eraseObject(state);

	this->removeChild(state);
	updateStateLayout();
}


void BaseCharacter::updateHPLabel() {
	__String *cache = __String::create(Value(m_hp).asString() + " /" + Value(m_max_hp).asString());
	m_hp_label->setString(cache->getCString());
}
void BaseCharacter::updateStateLayout() {
	int num = m_state_vector.size();
	//int row = num / STATE_NUM_PER_ROW;	//行数

	for (int i = 0; i < num; i++) {
		int row = i / STATE_NUM_PER_ROW;
		int column = i % STATE_NUM_PER_ROW;

		BaseState* state = m_state_vector.at(i);
		state->setPosition( 
			-m_sprite->getContentSize().width * m_sprite->getScale() /2 + ( m_sprite->getContentSize().width * m_sprite->getScale() - 32 * STATE_NUM_PER_ROW) / 2 + column * 32  ,
			m_hp_label->getPositionY() - m_hp_label->getContentSize().width/2 -  row * 32);
	}

}

void BaseCharacter::effect_when_round_end() {
	toEffectState();
}