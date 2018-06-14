#include"Player.h"

Player::Player(){
	m_Magic = 0;
	m_isHaveMagic = false;
}
Player::~Player(){

}

Player* Player::create(std::string picPath, int max_hp, int armor, int power, int agility, int magic , int max_cost ) {
	Player* pRet = new(std::nothrow)Player();
	if (pRet && pRet->init(picPath, max_hp, armor, power, agility, magic,max_cost)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool Player::init(std::string picPath, int max_hp, int armor, int power, int agility, int magic , int max_cost ) {
	if ( !BaseCharacter::init(picPath, max_hp , false, armor, power, agility)) {
		return false;
	}
	//初始化智力Label
	m_magic_label = Label::create("Magic: 0", "Arical", 16);
	m_magic_label->setAnchorPoint(Point(1.0, 0.5));
	m_magic_label->setPosition(
		-m_sprite->getContentSize().width / 2 - m_power_label->getContentSize().width / 2 - 2 , 
		m_agility_label->getPositionY() - m_agility_label->getContentSize().height);
	this->addChild(m_magic_label, 3);
	
	changeMagic( magic );

	m_max_cost = max_cost;
	m_cost = m_max_cost;

	return true;
}

void Player::changeMagic(int magic) {
	m_Magic += magic;
	m_isHaveMagic = m_Magic != 0 ? true : false;
	m_magic_label->setString("Magic: " + Value(m_Magic).asString());
	//向BaseCard发送信息，使得更新数据
	if (!m_isEnemy)
		__NotificationCenter::getInstance()->postNotification(MSG_PLAYER_PROPERTY_CHANGE, this);
}

void Player::changeCost(int cost) {
	m_cost += cost;
	if (m_cost < 0) {
		m_cost = 0;
	}
	//我觉得允许费用超出最大费用，如使用卡牌额外获得一费
	//if (m_cost > m_max_cost) {
	//	m_cost = m_max_cost;
	//}
}
void Player::changeMaxCost(int max_cost) {
	int dif = max_cost - m_max_cost;
	m_max_cost = max_cost;
	if (dif > 0) {
		changeCost(dif);	//如果差值大于0，则补上差值部分
	}
	else if (dif < 0) {	//觉得差值小于0的话可以不用管？
	}
}

void Player::effect_when_round_end() {
	this->resetCost();
	BaseCharacter::effect_when_round_end();
}