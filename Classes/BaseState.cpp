#include"BaseState.h"

bool BaseState::init(StateType type, std::string picPath, std::string name, std::string info, int rounds,  bool isCanEffect, bool isTemporary, bool isCanOverlay) {
	if (!Node::init()) {
		return false;
	}

	m_icon_sprite = Sprite::create(picPath);
	this->addChild(m_icon_sprite);

	m_name = name;
	m_info = info;
	m_continues_rounds = rounds;
	m_left_rounds = m_continues_rounds;

	m_continues_rouds_label = Label::create(Value(m_left_rounds).asString(), "Arical", 16);
	m_continues_rouds_label->setPosition(m_icon_sprite->getContentSize().width / 2, -m_icon_sprite->getContentSize().height / 2);
	this->addChild(m_continues_rouds_label);
	if (m_left_rounds < 0) {
		m_continues_rouds_label->setVisible(false);
	}

	m_type = type;
	m_isCanEffect = isCanEffect;
	m_isTemporary = isTemporary;
	m_isCanOverLay = isCanOverlay;

	//´¥Åö¼àÌýÆ÷
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(BaseState::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(BaseState::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool BaseState::onTouchBegan(Touch* pTouch, Event* pEvent) {
	Rect rect = Rect( this->getParent()->getPositionX() + this->getPositionX() - m_icon_sprite->getContentSize().width / 2, 
		this->getParent()->getPositionY() + this->getPositionY() - m_icon_sprite->getContentSize().height / 2,
		m_icon_sprite->getContentSize().width, m_icon_sprite->getContentSize().height);

	if ( rect.containsPoint(pTouch->getLocation())) {
		auto label = Label::create(m_name + "\n" + m_info, "Arical", 16 );
		label->setLineBreakWithoutSpace(true);
		label->setWidth(200);
		label->setPosition(0, -m_icon_sprite->getContentSize().height / 2 - 10);
		this->addChild(label, 3, 100);
		return true;
	}
	return false;
}

void BaseState::onTouchEnded(Touch* pTouch, Event* pEvent) {
	auto label = getChildByTag(100);
	label->setVisible(false);
	label->removeFromParent();
}