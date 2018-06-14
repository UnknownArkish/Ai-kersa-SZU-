#include"BaseLibrary.h"

BaseLibrary* BaseLibrary::create(std::string picPath, std::vector<CardID>& cardID) {
	BaseLibrary* pRet = new(std::nothrow)BaseLibrary();
	if (pRet && pRet->init(picPath, cardID)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
BaseLibrary* BaseLibrary::create(std::string picPath) {
	BaseLibrary* pRet = new(std::nothrow)BaseLibrary();
	if (pRet && pRet->init(picPath)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}


bool BaseLibrary::init(std::string picPath, std::vector<CardID>& cardID) {
	if (!Node::init()) {
		return false;
	}
	for (CardID id : cardID ) {
		addCard(id);
	}

	m_library_sprite = Sprite::create(picPath);
	this->addChild(m_library_sprite);

	return true;
}
bool BaseLibrary::init(std::string picPath) {
	if (!Node::init()) {
		return false;
	}
	m_library_sprite = Sprite::create(picPath);
	this->addChild(m_library_sprite);

	return true;
}


BaseCard*& BaseLibrary::drawCard() {
	int index = ((int)rand()*101) % m_library.size();
	auto card = m_library.at(index);
	m_library.eraseObject(card);
	return card;
}

void BaseLibrary::addCard(BaseCard*& card) {
	m_library.pushBack(card);
}
void BaseLibrary::addCard(int cardID) {
	addCard((CardID)cardID);
}
void BaseLibrary::addCard(CardID cardID) {
	BaseCard* card = CardSystem::createCardByID(cardID);
	addCard( /*CardSystem::createCardByID(cardID)*/ card );
}

bool BaseLibrary::onTouchBegan(Touch* pTouch, Event* pEvent) {
	return false;
}