#include"GameSceneDemo.h"

Scene* GameSceneDemo::createScene() {
	auto scene = Scene::create();
	auto layer = GameSceneDemo::create();
	scene->addChild(layer);
	return scene;
}

bool GameSceneDemo::init() {
	if (!Layer::init()) {
		return false;
	}
	m_visibleSize = _director->getVisibleSize();

	m_current_rounds = 1;

	//添加背景
	Sprite* background = Sprite::create("background/forest.png");
	float xScale = m_visibleSize.width / background->getContentSize().width;
	float yScale = m_visibleSize.height / background->getContentSize().height;
	background->setScale(xScale > yScale ? xScale : yScale);
	background->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
	this->addChild(background);

	//初始化玩家
	m_player = Player::create("character/player.png", 80, 0, 0, 0, 0, 3);
	m_player->setPosition( m_visibleSize.width * 3 / 13 , m_visibleSize.height * 6.5 / 13 );
	this->addChild(m_player , 0 , "player");

	//初始化敌人1
	auto enemy_1 = BaseEnemy::create("character/enemy.png", 100, 0, 0, 0 , EnemyType::Demo_Enemy);
	enemy_1->setPosition(m_visibleSize.width * 8 / 13, m_visibleSize.height * 6.5 / 13);
	this->addChild(enemy_1);
	m_enemys.pushBack(enemy_1);

	auto enemy_2 = BaseEnemy::create("character/enemy.png", 100, 0, 0, 0 , EnemyType::Demo_Enemy);
	enemy_2->setPosition(m_visibleSize.width * 11 / 13, m_visibleSize.height * 6.5 / 13);
	this->addChild(enemy_2);
	m_enemys.pushBack(enemy_2);

	//初始化回合Label
	m_cost_label = Label::create( "", "Arical", 24);
	m_cost_label->setPosition(
		m_visibleSize.width * (1 - touchableSize.width) / 2, 
		m_visibleSize.height * touchableSize.height + m_cost_label->getContentSize().height
	);
	this->addChild(m_cost_label);

	//模拟回合结束的按钮
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameSceneDemo::endRound, this));

	closeItem->setPosition(Vec2( m_visibleSize.width - closeItem->getContentSize().width / 2,
		closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//初始化卡牌
	std::vector<CardID> cardIDs;
	cardIDs.push_back(CardID::Strike);
	cardIDs.push_back(CardID::Strike);
	cardIDs.push_back(CardID::Strike);
	cardIDs.push_back(CardID::Strike);
	cardIDs.push_back(CardID::Defend);
	cardIDs.push_back(CardID::Defend);
	cardIDs.push_back(CardID::Defend);
	cardIDs.push_back(CardID::Inner_Strength);
	cardIDs.push_back(CardID::Armor_Breaking);
	cardIDs.push_back(CardID::Blessing_Of_Prince_Daughter);
	cardIDs.push_back(CardID::Blessing_Of_Prince_Daughter);
	cardIDs.push_back(CardID::Health_Potion);
	cardIDs.push_back(CardID::Mortal_Strike);
	cardIDs.push_back(CardID::Preparation);
	cardIDs.push_back(CardID::Cleave);
	cardIDs.push_back(CardID::Split);
	cardIDs.push_back(CardID::Pot_of_Avarice);
	cardIDs.push_back(CardID::Pot_of_Avarice);
	cardIDs.push_back(CardID::Burst_Limit);
	cardIDs.push_back(CardID::Tie);
	cardIDs.push_back(CardID::Magic_Missile);
	cardIDs.push_back(CardID::Magic_Missile);
	cardIDs.push_back(CardID::Magic_Book);
	cardIDs.push_back(CardID::Magic_Book);
	cardIDs.push_back(CardID::Magic_Book);
	cardIDs.push_back(CardID::Enchanted_Weapon);
	cardIDs.push_back(CardID::Arcane_Breath);

	m_card_layer = CardLayer_::create( cardIDs );
	this->addChild(m_card_layer);

	for (int i = 0; i < INIT_HAND_CARD_NUM; i++) {
		m_card_layer->drawCard();
	}

	m_ai_manager = AIManager::create(m_player, m_enemys);
	this->addChild(m_ai_manager);

	//添加触摸监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameSceneDemo::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameSceneDemo::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameSceneDemo::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	return true;
}

Target GameSceneDemo::getTarget(BaseBehaviour* behaviour) {
	Target target;
	target.isReady = true;
	switch (behaviour->m_target_need.enemy_need) {
		case 0:
			break;
		case 1:target.enemys.pushBack((BaseEnemy*)behaviour->getParent());
			break;
		case -1:
			target.enemys = m_enemys;
			break;
	}
	if (behaviour->m_target_need.player_need) {
		target.players.pushBack(m_player);
	}
	if (behaviour->m_target_need.card_layer_need) {
		target.cardLayers.pushBack(m_card_layer);
	}
	return target;
}
Target GameSceneDemo::getTarget(BaseCard* card) {
	Target target;
	target.isReady = true;

	int current_cost = m_player->getCost();
	if ( card->getCardCost() > current_cost) {
		target.isReady = false;
		CCLOG("I do not have enough cost");
	}
	switch (card->m_target_need.enemy_need) {
		case 0:
			break;

		case 1:
			if (m_current_enemy == NULL) {
				target.isReady = false;
			}
			else {
				target.enemys.pushBack(m_current_enemy);
			}
			break;

		case -1:
			target.enemys = m_enemys;
			break;
	}

	if (card->m_target_need.player_need) {
		target.players.pushBack(m_player);
	}
	if (card->m_target_need.card_layer_need) {
		target.cardLayers.pushBack(m_card_layer);
	}

	if (target.isReady) {
		m_player->changeCost( -card->getCardCost());
	}

	return target;
}

void GameSceneDemo::update(float dt) {
	updateCostLabel();
}

void GameSceneDemo::endRound(Ref* pRef) {
	m_current_rounds++;

	m_ai_manager->effect_when_round_end(m_current_rounds);	//结束回合更新AI、同时更新敌人
	m_player->effect_when_round_end();	//结束回合更新玩家
	m_card_layer->effect_when_round_end();	//结束回合使卡牌Layer抽牌
}

bool GameSceneDemo::onTouchBegan(Touch* pTouch, Event* pEvent) {
	CCLOG("GAMESCENE-TOUCH");
	m_current_enemy = NULL;
	/*if (m_card_layer->getIsSelect()) {
		return true;
	}
	return false;*/
	return true;
}
void GameSceneDemo::onTouchMoved(Touch* pTouch, Event* pEvent) {
	//CCLOG("GAMESCENE-TOUCH-MOVED");
	for (BaseEnemy* enemy : m_enemys) {
		if (enemy->getBoundingBox().containsPoint( pTouch->getLocation() )) {
			m_current_enemy = enemy;
		}
	}
}
void GameSceneDemo::onTouchEnded(Touch* pTouch, Event* pEvent) {
	CCLOG("GAMESCENE-TOUCH-END");
	for (BaseEnemy* enemy : m_enemys) {
		if (enemy->getBoundingBox().containsPoint( pTouch->getLocation() )) {
			m_current_enemy = enemy;
			return;
		}
	}
	m_current_enemy = NULL;
}


void GameSceneDemo::onMouseMove(EventMouse* pEvent) {
	//for (BaseEnemy* enemy : m_enemys) {
	//	if (enemy->getBoundingBox().containsPoint(Vec2(pEvent->getCursorX(), pEvent->getCursorY()))) {
	//		m_current_enemy = enemy;
	//		return;
	//	}
	//}
	//m_current_enemy = NULL;
}

void GameSceneDemo::updateCostLabel() {
	__String *cache = __String::create(Value(m_player->getCost()).asString() + " /" + Value(m_player->getMaxCost()).asString());
	m_cost_label->setString(cache->getCString());
}