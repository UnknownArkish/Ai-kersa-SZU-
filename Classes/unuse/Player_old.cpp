#include"Player_old.h"

Player_::Player_() {
	m_hp = 0;
	m_max_hp = 0;

	//初始化赋值
	m_Armor = 0;
	m_Power = 0;
	m_Agility = 0;
	m_Magic = 0;

	m_isDead = false;

	m_isHaveArmor = false;
	m_isHavePower = false;
	m_isHaveAgility = false;
	m_isHaveMagic = false;
}
Player_::~Player_() {

}

Player_* Player_::create(std::string picPath, int max_hp, int armor, int power, int agility, int magic) {
	Player_* pRet = new(std::nothrow)Player_();
	if ( pRet && pRet->init(picPath, max_hp , armor , power , agility , magic) ) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Player_::init(std::string picPath, int max_hp, int armor, int power, int agility, int magic) {
	if (!Node::init()) {
		return false;
	}

	//初始化人物精灵
	m_Player__sprite = Sprite::create(picPath);
	m_Player__sprite->setPosition(0, 0);
	this->addChild(m_Player__sprite , 5);

	//初始化HP_Label
	m_hp_label = Label::create("0 /0", "Arical", 16);
	m_hp_label->setPosition( 0, - m_Player__sprite->getContentSize().height / 2 - 10);
	this->addChild(m_hp_label , 3);

	//初始化护甲Label
	m_armor_label = Label::create("Armor: 0", "Arical", 20);
	m_armor_label->setPosition( 0 , m_Player__sprite->getContentSize().height / 2 + 20);
	this->addChild(m_armor_label, 3);

	//初始化力量、敏捷、智力Label
	m_power_label = Label::create("Power: 0", "Arical", 16);
	m_power_label->setAnchorPoint(Vec2(1.0, 0.5));
	m_power_label->setPosition( 
		-m_Player__sprite->getContentSize().width/2 - m_power_label->getContentSize().width /2 -2 , 0);
	this->addChild(m_power_label, 3);

	m_agility_label = Label::create("Agility: 0", "Arical", 16);
	m_agility_label->setAnchorPoint(Point(1.0, 0.5));
	m_agility_label->setPosition( 
		-m_Player__sprite->getContentSize().width/2 - m_power_label->getContentSize().width / 2 - 2, m_power_label->getPositionY() - m_power_label->getContentSize().height );
	this->addChild(m_agility_label, 3);

	m_magic_label = Label::create("Magic: 0", "Arical", 16);
	m_magic_label->setAnchorPoint(Point(1.0, 0.5));
	m_magic_label->setPosition( 
		-m_Player__sprite->getContentSize().width/2 - m_power_label->getContentSize().width / 2 - 2, m_agility_label->getPositionY() - m_agility_label->getContentSize().height );
	this->addChild(m_magic_label, 3);


	this->changeMaxHP(max_hp);
	this->changeArmor(armor);
	this->changePower(power);
	this->changeAgility(agility);
	this->changeMagic(magic);

	return true;
}

void Player_::hurt(int damage) {
	if (m_isHaveArmor) {	//如果有护甲值
		if ( damage > m_Armor) {
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
}
void Player_::heal(int health) {
	m_hp += health;
	if (m_hp > m_max_hp) {
		m_hp = m_max_hp;
	}
	updateHPLabel();
}

void Player_::changeMaxHP(int max_hp) {
	//如果改变的最大生命值大于现在的，则需要补差值
	if (max_hp > m_max_hp) {
		m_hp  += (max_hp - m_max_hp);
	}
	//如果改变的最大生命值小于现在同时小于当前生命值，则把当前生命设为改变后的数值
	else if( max_hp < m_max_hp && max_hp < m_hp ){	
		m_hp = max_hp;
	}
	m_max_hp = max_hp;

	updateHPLabel();
}

void Player_::changeArmor(int armor) {
	m_Armor += armor;
	m_isHaveArmor = m_Armor > 0 ? true : false;
	m_power_label->setString("Armor: " + Value(m_Armor).asString());
}
void Player_::changePower(int power) {
	m_Power += power;
	m_isHavePower = m_Power != 0 ? true : false;
	m_power_label->setString("Power: " + Value(m_Power).asString());
}
void Player_::changeAgility(int agility) {
	m_Agility += agility;
	m_isHaveAgility = m_Agility != 0 ? true : false;
	m_agility_label->setString("Agility: " + Value(m_Agility).asString());
}
void Player_::changeMagic(int magic) {
	m_Magic += magic;
	m_isHaveMagic = m_Magic != 0 ? true : false;
	m_magic_label->setString("Magic: " + Value(m_Magic).asString());
}


void Player_::updateHPLabel() {
	__String *cache = __String::create(Value(m_hp).asString() + " /" + Value(m_max_hp).asString());
	m_hp_label->setString( cache->getCString() );
}

