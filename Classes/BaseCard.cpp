#include"BaseCard.h"
#include"Player.h"

BaseCard::BaseCard() {

}
BaseCard::~BaseCard() {
	__NotificationCenter::getInstance()->removeAllObservers(this);
}

BaseCard* BaseCard::create(CardID cardID, std::string name, std::string info, std::string cost , std::string picPath, b2World* world) {
	BaseCard* pRet = new(std::nothrow)BaseCard();
	if (pRet && pRet->init(cardID,  name, info, cost , picPath,world)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool BaseCard::init(CardID cardID, std::string name, std::string info , std::string cost , std::string picPath, b2World* world) {
	if (!Node::init()) {	//初始化父类
		return false;
	}
	//卡牌图案
	m_cardSprite = Sprite::create(picPath);
	this->addChild(m_cardSprite);

	m_card_ID = cardID;
	m_cardName = name;
	m_cardInfo = info;
	m_cardCost = cost;
	m_pre_cardCost = Value(m_cardCost).asInt();


	//初始化名字Label
	m_cardName_label = Label::create(m_cardName, "Arical", 32);
	m_cardName_label->setPosition( 0, m_cardSprite->getContentSize().height * 3 / 8 );
	this->addChild(m_cardName_label);
	
	//初始化说明Label
	m_cardInfo_label = Label::create(m_cardInfo, "Arical", 24);
	m_cardInfo_label->setAnchorPoint(Point(0.5, 1));
	m_cardInfo_label->setLineBreakWithoutSpace(true);
	m_cardInfo_label->setWidth(m_cardSprite->getContentSize().width - 10);
	m_cardInfo_label->setAlignment(CCTextAlignment::CENTER);
	this->addChild(m_cardInfo_label);

	//updateCardInfo();

	//初始化费用Label
	m_cardCost_label = Label::create( m_cardCost, "Arical", 24);
	m_cardCost_label->setPosition( -m_cardSprite->getContentSize().width * 3 / 8, m_cardSprite->getContentSize().height * 3 / 8);
	this->addChild(m_cardCost_label);

	//创建Body、Shapre、Fixture
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_cardSprite->getPositionX() / PTM_RATIO, m_cardSprite->getPositionY() / PTM_RATIO);
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape poly;
	poly.SetAsBox(m_cardSprite->getContentSize().width / 2 / PTM_RATIO, m_cardSprite->getContentSize().height / 2 / PTM_RATIO);
	m_body->CreateFixture(&poly, 0.0f);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(BaseCard::updateCardProperty), MSG_PLAYER_PROPERTY_CHANGE, NULL);
	
	this->scheduleUpdate();

	////添加鼠标事件监听器
	//auto listener = EventListenerMouse::create();
	//listener->onMouseMove = CC_CALLBACK_1(BaseCard::onMouseMove, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void BaseCard::effect(Target& target) {
	for each (BaseEffect* var in m_effect_vector){
		var->effect(target);
	}
}

void BaseCard::addEffect(BaseEffect* effect) {
	m_effect_vector.pushBack(effect);
}

void BaseCard::update(float dt) {
	//更新Body的位置和旋转信息
	m_body->SetTransform(b2Vec2(this->getPositionX() / PTM_RATIO, this->getPositionY() / PTM_RATIO),
		CC_DEGREES_TO_RADIANS(this->getRotation()));
}
void BaseCard::updateCardProperty(Ref* pSender) {
	Player* player = (Player*)pSender;
	if (m_pre_property.damage_number != 0 && -player->getPower() + m_pre_property.damage_number != m_Property.damage_number) {
		m_Property.damage_number = -player->getPower() + m_pre_property.damage_number;
		updateCardInfo();
	}
	if (m_pre_property.armor_number != 0 && player->getAgility() + m_pre_property.armor_number != m_Property.armor_number){
		m_Property.armor_number = player->getAgility() + m_pre_property.armor_number;
		updateCardInfo();
	}
	if ( player->getMagic() + m_pre_property.magic_number != m_Property.magic_number) {
		m_Property.magic_number = player->getMagic() + m_pre_property.magic_number;
		if (m_card_type == CardType::Magic_Card) {
			int cost = (m_pre_cardCost - m_Property.magic_number);
			cost = cost < 0 ? 0 : cost;
			m_cardCost = Value(cost).asString();
			m_cardCost_label->setString(m_cardCost);
		}
	}
}
void BaseCard::updateCardInfo() {
	std::string power = "[damage]";
	int i = m_cardInfo.find(power);
	if (i != -1) {
		std::string after_update = m_cardInfo.substr(0, i) + Value(-m_Property.damage_number).asString() + m_cardInfo.substr(i + power.length(), m_cardInfo.length());
		m_cardInfo_label->setString(after_update);
	}

	std::string armor = "[armor]";
	i = m_cardInfo.find(armor);
	if (i != -1) {
		std::string after_update = m_cardInfo.substr(0, i) + Value(m_Property.armor_number).asString() + m_cardInfo.substr(i + armor.length(), m_cardInfo.length());
		m_cardInfo_label->setString(after_update);
	}
}

void BaseCard::moveTo(Point position, float time) {
	this->runAction(MoveTo::create(time, position));
}
void BaseCard::rotateTo(float rotation, float time) {
	this->runAction(RotateTo::create(time,rotation));
}

void BaseCard::onMouseMove(EventMouse* pEvent) {
	//Rect rect = Rect(this->getPositionX() - m_cardSprite->getContentSize().width / 2, this->getPositionY() - m_cardSprite->getContentSize().height / 2,
	//	m_cardSprite->getContentSize().width, m_cardSprite->getContentSize().height);
	//if (rect.containsPoint(Vec2(pEvent->getCursorX(), pEvent->getCursorY()))) {
	//	
	//}
}