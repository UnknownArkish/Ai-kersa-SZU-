#include"DemoScene_.h"

Scene* DemoScene_::createScene() {
	Scene* scene = Scene::create();
	Layer* layer = DemoScene_::create();
	scene->addChild(layer);
	return scene;
}

bool DemoScene_::init() {
	if (!Layer::init()) {
		return false;
	}
	m_visiableVize = _director->getVisibleSize();

	std::vector<CardID> cardID;
	cardID.push_back(CardID::Strike);
	cardID.push_back(CardID::Defend);
	cardID.push_back(CardID::Inner_Strength);
	cardID.push_back(CardID::Mortal_Strike);
	cardID.push_back(CardID::Armor_Breaking);
	cardID.push_back(CardID::Blessing_Of_Prince_Daughter);

	//²âÊÔBaseLibrary
	library = BaseLibrary::create("icons/library.png", cardID);
	library->setPosition(m_visiableVize.width / 2, m_visiableVize.height / 2);
	this->addChild(library);


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(DemoScene_::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(DemoScene_::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(DemoScene_::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	return true;
}

void DemoScene_::update(float dt) {
	if (m_flag) {
		m_flag = false;
		card->setPosition(m_visiableVize.width / 2, m_visiableVize.height / 2);
		this->addChild(card);
	}
}

bool DemoScene_::onTouchBegan(Touch* pTouch, Event* pEvent) {
	card = library->drawCard();
	m_flag = true;

	//auto sprite = Sprite::create("icons/library.png");
	//sprite->setPosition(m_visiableVize.width / 2, m_visiableVize.height / 2);
	//this->addChild(sprite);

	return true;
}

void DemoScene_::onTouchMoved(Touch* pTouch, Event* pEvent) {

}
void DemoScene_::onTouchEnded(Touch* pTouch, Event* pEvent) {
}