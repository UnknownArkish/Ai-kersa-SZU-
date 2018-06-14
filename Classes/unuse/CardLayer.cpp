#include"CardLayer.h"

CardLayer* CardLayer::create(std::vector<CardID>& cardIDs) {
	CardLayer* pRet = new(std::nothrow)CardLayer();
	if (pRet && pRet->init(cardIDs)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool CardLayer::init(std::vector<CardID>& cardIDs) {
	if (!Layer::init()) {
		return false;
	}
	m_visibleSize = _director->getVisibleSize();

	m_card_library = BaseLibrary::create("icons/library.png", cardIDs);
	m_card_library->setPosition( m_visibleSize.width * 1 / 16, m_visibleSize.height * 1 / 6);
	this->addChild(m_card_library);

	m_discard_library = BaseLibrary::create("icons/discard.png");
	m_discard_library->setPosition(m_visibleSize.width * 15 / 16, m_visibleSize.height * 1 / 6);
	this->addChild(m_discard_library);

	updateLayout();

	auto listener = EventListenerMouse::create();
	listener->onMouseMove = CC_CALLBACK_1(CardLayer::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto listener_ = EventListenerTouchOneByOne::create();
	listener_->onTouchBegan = CC_CALLBACK_2(CardLayer::onTouchBegan, this);
	listener_->onTouchMoved = CC_CALLBACK_2(CardLayer::onTouchMoved, this);
	listener_->onTouchEnded = CC_CALLBACK_2(CardLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_, this);

	this->scheduleUpdate();

	return true;
}

bool CardLayer::drawCard() {
	//如果抽牌库和弃牌库同时为0，就无法抽牌了
	if (m_card_library->getLibrarySize() == 0 && m_discard_library->getLibrarySize() == 0) {
		return false;
	}

	//如果抽牌库为空，那么先把弃牌库中所有牌放置抽牌库中
	if (m_card_library->getLibrarySize() == 0) {
		while (m_discard_library->getLibrarySize() != 0) {
			m_card_library->addCard(m_discard_library->drawCard());
		}
	}

	auto card = m_card_library->drawCard();
	m_hand_cards.pushBack(card);

	updateLayout();	//更新布局

	return true;
}

bool CardLayer::drawFromDisLibraryToHand() {
	if (m_discard_library->getLibrarySize() == 0) {
		return false;
	}

	auto card = m_discard_library->drawCard();
	m_hand_cards.pushBack(card);

	updateLayout();
	return true;
}
bool CardLayer::drawFromDisLibraryToCardLibrary() {
	if (m_discard_library->getLibrarySize() == 0) {
		return false;
	}

	m_card_library->addCard(m_discard_library->drawCard());
	return true;
}

bool CardLayer::addCardToHand(BaseCard*& card) {
	if (m_hand_cards.size() == MAX_HAND_CARD_NUM) {	//如果等于卡牌上限则移入弃牌库
		addCardToDisLibrary(card);
		return false;
	}
	else {
		this->addChild(card);

		m_hand_cards.pushBack(card);
		updateLayout();
		return true;
	}
}
void CardLayer::addCardToCardLibrary(BaseCard*& card) {
	this->addChild(card);	//添加至父节点，设置为不可见
	card->setVisible(false);

	m_card_library->addCard(card);
}
void CardLayer::addCardToDisLibrary(BaseCard*& card) {
	this->addChild(card);	//添加至父节点，设置为不可见
	card->setVisible(false);

	m_discard_library->addCard(card);
}

void CardLayer::updateLayout() {
	int card_num = m_hand_cards.size();
	if (card_num == 0)	return;

	int mid = card_num / 2;
	float space = m_visibleSize.width * touchableSize.width / (m_hand_cards.size() + 1) * card_num / MAX_HAND_CARD_NUM;

	for (int i = 0; i < card_num; i++) {
		BaseCard* card = m_hand_cards.at(i);
		card->setVisible(true);

		float x;
		float x_;
		if (i <= mid) {
			x = -(mid - i) * space;
			if (i != mid) {
				x_ = -(mid - i - 1) * space + m_visibleSize.width / 2;
			}
			else {
				x_ = x + m_visibleSize.width / 2;
			}
		}
		else {
			x = (i - mid) * space;
			x_ = (i - mid - 1) * space + m_visibleSize.width / 2;
		}
		float y = -2 * card->getContentSize().height / (m_visibleSize.width * touchableSize.width) / (m_visibleSize.width * touchableSize.width) * x * x +
			card->getContentSize().height * 3 / 7;
		card->setPosition(x + m_visibleSize.width / 2, y);
		Vec2 rot = Vec2(x + m_visibleSize.width / 2, y) - Vec2(x_, -m_visibleSize.height / 3);
		if (i < mid) {
			card->setRotation( CC_RADIANS_TO_DEGREES(rot.getAngle() - 90 ));
		}
		else {
			card->setRotation(90 - CC_RADIANS_TO_DEGREES(rot.getAngle()));
		}
	}
}

void CardLayer::update(float dt) {
	for (int i = 0; i < m_hand_cards.size() ; i++) {
		BaseCard* card = m_hand_cards.at(i);
		if (card != m_current_card) {
			card->setScale(1.0f);
			card->setZOrder(i);
		}
	}
	//drawCard();
}

bool CardLayer::onTouchBegan(Touch* pTouch, Event* pEvent) {
	if (m_isHovor) {
		m_isSelect = true;
		return true;
	}
	else {
		return false;
	}
}
void CardLayer::onTouchMoved(Touch* pTouch, Event* pEvent) {
	m_current_card->setPosition(pTouch->getLocation());
}
void CardLayer::onTouchEnded(Touch* pTouch, Event* pEvent) {
	if (pTouch->getLocation().y > m_visibleSize.height * touchableSize.height) {
		m_hand_cards.eraseObject(m_current_card);
		m_discard_library->addCard(m_current_card);
		m_current_card->setVisible(false);
	}
	updateLayout();
	m_isSelect = false;
	m_isHovor = false;
	m_current_card = NULL;
}

void CardLayer::onMouseMove(EventMouse* pEvent) {
	if (!m_isSelect) {
		b2AABB touchAABB;	//触碰点AABB
		touchAABB.lowerBound.Set(pEvent->getCursorX() / PTM_RATIO - 0.0001, pEvent->getCursorY() / PTM_RATIO - 0.0001);
		touchAABB.upperBound.Set(pEvent->getCursorX() / PTM_RATIO + 0.0001, pEvent->getCursorY() / PTM_RATIO + 0.0001);

		for (int i = m_hand_cards.size() - 1; i >= 0; i--) {
			BaseCard* card = m_hand_cards.at(i);
			if (card->getBody()->GetFixtureList()->GetAABB(0).Contains(touchAABB)) {
				card->setScale(1.25f);
				card->setZOrder(10);

				m_current_card = card;
				m_isHovor = true;
				return;
			}
		}
		m_current_card = NULL;
		m_isHovor = false;
		return;
	}
}