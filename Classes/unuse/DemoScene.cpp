#include"DemoScene.h"
#include"DamageEffect.h"
#include"Player.h"
#include"BaseEnemy.h"
#include"BaseState.h"
#include"CardSystem.h"

Scene* DemoScene::createScene() {
	auto scene = Scene::create();
	auto layer = DemoScene::create();
	scene->addChild(layer);
	return scene;
}

bool DemoScene::init() {
	if (!Layer::init()) {
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	//测试Player√
	player= Player::create("character/player.png", 80, 0, 0, 0, 9 , 3);
	player->setPosition(visibleSize.width * 1 / 4, visibleSize.height / 2);
	this->addChild(player);

	////测试敌人√
	//enemy = BaseEnemy::create("character/player.png", 100, 15, 3, 2);
	//enemy->setPosition(visibleSize.width * 3 / 4, visibleSize.height / 2);
	//this->addChild(enemy);

	//测试卡牌系统√
	//测试内在潜力、打击、防御√
	//测试致死打击、破甲√
	//测试王女的祝福√
	baseCard = CardSystem::createCardByID(CardID::Armor_Breaking);
	baseCard->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(baseCard);

	////测试手上卡牌Layer
	//m_handCard = HandCardLayer::create(5);
	//this->addChild(m_handCard);

	//模拟回合结束的按钮
	auto mybutton = Button::create("CloseNormal.png", "CloseNormal.png", "CloseNormal.png");
	mybutton->setPosition( Vec2((int)(visibleSize.width / 2 ), 50) );
	mybutton->addTouchEventListener( CC_CALLBACK_2(DemoScene::testFunction, this ) );
	this->addChild(mybutton);

	//std::vector<CardID> cardID;
	//cardID.push_back(CardID::Strike);
	//cardID.push_back(CardID::Defend);
	//cardID.push_back(CardID::Inner_Strength);
	//cardID.push_back(CardID::Mortal_Strike);
	//cardID.push_back(CardID::Armor_Breaking);
	//cardID.push_back(CardID::Blessing_Of_Prince_Daughter);

	////测试BaseLibrary
	//library = BaseLibrary::create("icons/library.png" , cardID);
	//library->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//this->addChild(library);

	//BaseCard* card = library->drawCard();

	//Target target;
	//if (card->getPlayerNeed())
	//	target.players.pushBack(player);
	//switch (card->getEnemyNeed) {
	//	case 0:
	//		break;
	//	case 1:
	//		target.enemys.pushBack(enemy);
	//		break;
	//	case -1:
	//		break;
	//}
	//this->addChild(card);


	//测试PowerChangeState是否生效√
	//powerState = PowerChangeState::create("icons/armor.png", "Demo" ,"demo", -1, 3, true);
	//player->addState(powerState);

	////测试基类State
	//auto baseState = BaseState::create("icons/armor.png", "Armor", "armor armor ", -1);
	//baseState->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//this->addChild(baseState);

	////测试PowerUpState
	//powerUpState = PowerUpState::create("icons/armor.png", "Armor", "Get 3 Power when your rounds end", -1, 3);
	//player->addChild(powerUpState);	//把状态附在人物身上


	//// 测试数据库√
	//std::string filename = CCFileUtils::sharedFileUtils()->fullPathForFilename("sql/sql.db");
	//std::string sql; // sql语句
	//int ret;         // 执行结果，SQLITE_OK表示成功执行

	//this->pdb = nullptr;
	//ret = sqlite3_open(filename.c_str(), &pdb);
	//if (ret != SQLITE_OK) {
	//	const char* errmsg = sqlite3_errmsg(pdb);
	//	CCLOG("sqlite open error: %s", errmsg);
	//	sqlite3_close(pdb);
	//	return false;
	//}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(DemoScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(DemoScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(DemoScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


//void DemoScene::onMouseMove(EventMouse* pEvent) {
//	CCLOG("%f %f", pEvent->getCursorX(), pEvent->getCursorY());
//}


//可用于模拟回合结束
bool DemoScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
	////测试卡牌effect效果
	//Target target;
	//if (baseCard->getPlayerNeed())
	//	target.players.pushBack(player);
	//switch (baseCard->getEnemyNeed()) {
	//	case 0:
	//		break;
	//	case 1:
	//		target.enemys.pushBack(enemy);
	//		break;
	//	case -1:
	//		break;
	//}
	//baseCard->effect(target);

	////CCLOG( Value(library->getLibrarySize()).asString().c_str() );
	////CCLOG( Value(baseCard->getCardID()).asString().c_str() );
	//BaseCard* card = library->drawCard();
	//card->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	////card->effect(characters);
	//this->addChild(card);


	//测试PowerChangeState effct是否生效√
	//powerState->effect();


	////测试数据库查找√
	//std::string sql = "select * from card_zh_cn where ID = " + Value(0).asString();
	//int ret = sqlite3_exec(pdb, sql.c_str(), &callback, (void*)"para", nullptr);

	return false;
}
void DemoScene::onTouchMoved(Touch* pTouch, Event* pEvent) {

}
void DemoScene::onTouchEnded(Touch* pTouch, Event* pEvent) {

}




void DemoScene::testFunction(Ref* pSender, Widget::TouchEventType event) {
	//测试DemageEffect是否生效
	//auto dameageEffect = DamageEffect::create(10);
	//dameageEffect->effect(player);

	//测试PowerChangeState是否生效
}

void DemoScene::update(float dt) {

}