#include"TestCardLayer.h"

Scene* TestCardLayer::createScene() {
	Scene* scene = Scene::create();
	Layer* layer = TestCardLayer::create();
	scene->addChild(layer);

	return scene;
}
bool TestCardLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	//std::vector<CardID> cardIDs;

	//cardIDs.push_back(CardID::Strike);
	//cardIDs.push_back(CardID::Defend);
	//cardIDs.push_back(CardID::Inner_Strength);
	//cardIDs.push_back(CardID::Armor_Breaking);
	//cardIDs.push_back(CardID::Blessing_Of_Prince_Daughter);
	//cardIDs.push_back(CardID::Health_Potion);
	//cardIDs.push_back(CardID::Mortal_Strike);
	//cardIDs.push_back(CardID::Preparation);

	//m_cardLayer = CardLayer_::create(cardIDs);
	//this->addChild(m_cardLayer);

	//auto listener = EventListenerKeyboard::create();
	//listener->onKeyPressed = CC_CALLBACK_2(TestCardLayer::onKeyPressed, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//for (int i = 0; i < 5; i++) {
	//	m_cardLayer->drawCard();
	//}

	return true;
}

void TestCardLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* pEvent) {
	//if (keyCode == EventKeyboard::KeyCode::KEY_Z) {
	//	m_cardLayer->drawCard();
	//	//this->addChild(CardSystem::createCardByID(CardID::Strike));
	//}
}