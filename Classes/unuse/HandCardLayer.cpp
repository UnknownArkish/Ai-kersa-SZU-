#include"HandCardLayer.h"

HandCardLayer* HandCardLayer::create(int cardNum) {
	HandCardLayer* pRet = new(std::nothrow)HandCardLayer();
	if (pRet && pRet->init(cardNum)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool HandCardLayer::init(int cardNum) {
	if ( !Layer::init() ) {
		return false;
	}
	//Size visibleSize = Director::getInstance()->getVisibleSize();

	//auto dictionary = Dictionary::createWithContentsOfFile("zh-cn.xml");

	//auto firstcard = BaseCard::create(((String*)(dictionary->objectForKey("strike")))->getCString(),
	//	((String*)(dictionary->objectForKey("strike_info")))->getCString(), ((String*)(dictionary->objectForKey("strike_cost")))->getCString(),
	//	"card/base_card.png");
	//firstcard->setPosition( visibleSize.width/2 , firstcard->getCardSprite()->getContentSize().height/2 );
	//m_handCardList.pushBack(firstcard);
	//this->addChild(firstcard);

	//for (int i = 1; i < cardNum; i++) {
	//	auto card = BaseCard::create(((String*)(dictionary->objectForKey("strike")))->getCString(),
	//		((String*)(dictionary->objectForKey("strike_info")))->getCString(), ((String*)(dictionary->objectForKey("strike_cost")))->getCString(),
	//		"card/base_card.png");
	//	if ( i % 2 == 1 ) {
	//		card->setPosition( firstcard->getPositionX() - (i+1)/2 * (card->getCardSprite()->getContentSize().width + 2 ) , firstcard->getPositionY());
	//	}
	//	else {
	//		card->setPosition( firstcard->getPositionX() + (i+1)/2 * (card->getCardSprite()->getContentSize().width + 2 ), firstcard->getPositionY());
	//	}
	//	m_handCardList.pushBack(card);
	//	this->addChild(card);
	//}

	//auto listener = EventListenerMouse::create();
	//listener->onMouseMove = CC_CALLBACK_1(HandCardLayer::onMouseMove, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	return true;
}

void HandCardLayer::update(float dt) {
	std::vector<BaseCard*>::iterator it = m_handCardList.begin();
	std::vector<BaseCard*>::iterator end = m_handCardList.end();
	for (int i = 0; it != end; it++ , i++ ) {
		BaseCard* card = *it;
		if (card != m_currentCard) {
			card->setScale(1.0f);
			card->setZOrder(i);
		}
	}
}

void HandCardLayer::onMouseMove(EventMouse* pEvent) {
	std::vector<BaseCard*>::iterator it = m_handCardList.begin();
	std::vector<BaseCard*>::iterator end = m_handCardList.end();
	for (; it != end; it++) {
		BaseCard* card = *it;
		Rect cardRect = Rect( card->getPositionX() - card->getCardSprite()->getContentSize().width / 2,
							card->getPositionY() - card->getCardSprite()->getContentSize().height / 2,
			card->getCardSprite()->getContentSize().width, card->getCardSprite()->getContentSize().height);
		if ( cardRect.containsPoint( Vec2(pEvent->getCursorX() , pEvent->getCursorY() ) )){
			m_currentCard = card;
			m_isHover = true;
			card->setScale(1.25f);
			card->setZOrder(10);
			return;
		}
	}
	m_isHover = false;
	m_currentCard = NULL;
	return;
}