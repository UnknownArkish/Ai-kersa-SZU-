#include"TestCardDiplayScene.h"

#include"CardSystem.h"
#include"CardDisplayLayer.h"


Scene* TestCardDisplayScene::createScene() {
	auto scene = Scene::create();
	auto layer = TestCardDisplayScene::create();
	scene->addChild(layer);
	return scene;
}
bool TestCardDisplayScene::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibileSize = _director->getVisibleSize();
	
	Vector<BaseCard*> cards;
	cards.pushBack(CardSystem::createCardByID(CardID::Strike));
	cards.pushBack(CardSystem::createCardByID(CardID::Strike));
	cards.pushBack(CardSystem::createCardByID(CardID::Strike));
	cards.pushBack(CardSystem::createCardByID(CardID::Strike));
	cards.pushBack(CardSystem::createCardByID(CardID::Strike));
	cards.pushBack(CardSystem::createCardByID(CardID::Strike));
	cards.pushBack(CardSystem::createCardByID(CardID::Strike));
	cards.pushBack(CardSystem::createCardByID(CardID::Strike));
	cards.pushBack(CardSystem::createCardByID(CardID::Strike));
	cards.pushBack(CardSystem::createCardByID(CardID::Strike));
	cards.pushBack(CardSystem::createCardByID(CardID::Strike));
	cards.pushBack(CardSystem::createCardByID(CardID::Strike));

	auto demo = CardDisplayLayer::create(cards);
	demo->setPosition(visibileSize.width * (1 - card_display_size.width) / 2, visibileSize.height * ( 1 - card_display_size.height ) / 2 );
	this->addChild(demo);

	return true;
}