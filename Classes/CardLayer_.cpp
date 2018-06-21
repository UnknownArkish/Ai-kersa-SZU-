#include"CardLayer_.h"
#include"CardDisplayLayer.h"
#include"CCShake.h"

CardLayer_* CardLayer_::create(std::vector<CardID>& cardIDs) {
	CardLayer_* pRet = new(std::nothrow)CardLayer_();
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

bool CardLayer_::init(std::vector<CardID> cardIDs) {
	if (!Layer::init()) {
		return false;
	}
	m_visibleSize = _director->getVisibleSize();

	m_card_library_button = MenuItemImage::create(
		"icons/library.png",
		"icons/library.png",
		CC_CALLBACK_1(CardLayer_::checkCardLibrary, this));
	m_card_library_button->setName("card_library_button");
	m_card_library_button->setPosition(m_visibleSize.width * 1 / 16, m_visibleSize.height * 1 / 8);

	m_dis_library_button = MenuItemImage::create(
		"icons/discard.png",
		"icons/discard.png",
		CC_CALLBACK_1(CardLayer_::checkCardLibrary, this));
	m_dis_library_button->setName("discard_library_button");
	m_dis_library_button->setPosition(m_visibleSize.width * 15 / 16, m_visibleSize.height * 1 / 8);

	auto menu = Menu::create(m_card_library_button, m_dis_library_button, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	m_card_library_label = Label::create("0", "Arical", 16);
	m_card_library_label->setPosition(m_card_library_button->getContentSize().width / 2, -m_card_library_button->getContentSize().height / 2);
	m_card_library_button->addChild(m_card_library_label);


	m_discard_library_label = Label::create("0", "Arical", 16);
	m_discard_library_label->setPosition(m_dis_library_button->getContentSize().width / 2, -m_dis_library_button->getContentSize().height / 2);
	m_dis_library_button->addChild(m_discard_library_label);

	for (CardID id : cardIDs) {
		auto card = CardSystem::createCardByID(id);
		addCardToCardLibrary(card);
	}


	for (int i = 0; i < LINE_SPRITE_NUMBER - 1; i++) {
		line[i] = Sprite::create("ui/reticleBlock.png");
		line[i]->setVisible(false);
		this->addChild(line[i]);
	}
	line[LINE_SPRITE_NUMBER - 1] = Sprite::create("ui/reticleArrow.png");
	line[LINE_SPRITE_NUMBER - 1]->setScale(0.8);
	line[LINE_SPRITE_NUMBER - 1]->setVisible(false);
	this->addChild(line[LINE_SPRITE_NUMBER - 1]);


	auto listener = EventListenerMouse::create();
	listener->onMouseMove = CC_CALLBACK_1(CardLayer_::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto listener_ = EventListenerTouchOneByOne::create();
	listener_->onTouchBegan = CC_CALLBACK_2(CardLayer_::onTouchBegan, this);
	listener_->onTouchMoved = CC_CALLBACK_2(CardLayer_::onTouchMoved, this);
	listener_->onTouchEnded = CC_CALLBACK_2(CardLayer_::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_, this);

	this->scheduleUpdate();

	return true;
}

void CardLayer_::clearLine() {
	for (int i = 0; i < LINE_SPRITE_NUMBER; i++) {
		line[i]->setVisible(false);
	}
}

BaseCard* CardLayer_::drawFromCardLibrary() {
	return drawFromCardLibraryAtID((rand() * 101) % m_card_library.size());
}
BaseCard* CardLayer_::drawFromCardLibraryAtID(int index) {
	if (m_card_library.size() == 0) {
		return NULL;
	}
	if (index < 0 || index >= m_card_library.size()) {
		return NULL;
	}
	BaseCard* card = m_card_library.at(index);
	m_card_library.eraseObject(card);
	m_card_library_label->setString(Value(m_card_library.size()).asString());
	return card;
}


BaseCard* CardLayer_::drawFromDisLibrary() {
	return drawFromDisLibraryAtID((rand() * 101) % m_discard_library.size());
}
BaseCard* CardLayer_::drawFromDisLibraryAtID(int index) {
	if (m_discard_library.size() == 0) {
		return NULL;
	}

	if (index < 0 || index >= m_discard_library.size()) {
		return NULL;
	}
	BaseCard* card = m_discard_library.at(index);
	m_discard_library.eraseObject(card);
	m_discard_library_label->setString(Value(m_discard_library.size()).asString());
	return card;
}


bool CardLayer_::drawCardAtID(int index) {	//一般来说这个都是index存在的，因为需要指定某张卡牌
											//如果卡牌数已达到上限
	if (m_hand_cards.size() == MAX_HAND_CARD_NUM) {
		return false;
	}

	auto card = drawFromCardLibraryAtID(index);
	if (card == NULL) {
		return false;
	}
	m_hand_cards.pushBack(card);
	card->setPosition(m_card_library_button->getPosition());
	card->setRotation(90 + rand() % 10);
	card->setScale(0);

	updateLayout();
	return true;
}
bool CardLayer_::drawCard() {
	//如果卡牌数已达到上限
	if (m_hand_cards.size() == MAX_HAND_CARD_NUM) {
		return false;
	}
	//如果抽牌库和弃牌库都没有牌了，那就没办法抽牌了
	if (m_card_library.size() == 0 && m_discard_library.size() == 0) {
		return false;
	}

	//如果只是抽牌库没有牌，则先从弃牌库中获得所有卡牌至抽牌库
	if (m_card_library.size() == 0) {
		while (m_discard_library.size() != 0) {
			m_card_library.pushBack(drawFromDisLibrary());
			//m_card_library.pushBack(m_discard_library.back());
			//m_discard_library.popBack();
		}
	}

	return drawCardAtID((rand() * 101) % m_card_library.size());
}
bool CardLayer_::drawCard(int num) {
	if (num == 0) {
		return true;
	}
	//如果超过抽牌库和弃牌库数量，则压为最大值
	if (num > m_card_library.size() + m_discard_library.size()) {
		num = m_card_library.size() + m_discard_library.size();
	}
	if (num == 0) {	//没有任何牌的情况下
		return false;
	}

	for (int i = 0; i < num; i++) {
		drawCard();
	}
	return true;
}
void CardLayer_::drawFull() {
	while (drawCard()) {	//一直抽牌，直到满或者没牌为止

	}
}


bool CardLayer_::discardAtID(int index, bool isDestory) {
	if (m_hand_cards.size() == 0) {
		return false;
	}

	if (index < 0 || index >= m_hand_cards.size()) {
		return false;
	}
	auto card = m_hand_cards.at(index);
	m_hand_cards.eraseObject(card);	//从手牌中去除

	auto func_ = [](BaseCard* card) {
		card->setVisible(false);	//设为不可见
	};
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Point(m_visibleSize.width * 11 / 17, m_visibleSize.height * 11 / 13);
	bezier.controlPoint_1 = Point(m_visibleSize.width * 14 / 17, m_visibleSize.height * 8 / 13);
	bezier.endPosition = m_dis_library_button->getPosition();
	card->runAction( Sequence::create(
		Spawn::create(
			BezierTo::create(0.5f, bezier),
			EaseSineIn::create( ScaleTo::create(0.5f, 0.28f)),
			RotateBy::create(0.2f, 90 - CC_RADIANS_TO_DEGREES((m_dis_library_button->getPosition() - card->getPosition()).getAngle())),
			NULL),
		CallFunc::create( std::bind(func_,card) ) , 
		NULL ));

	updateLayout();
	if (!isDestory) {
		m_discard_library.pushBack(card);
		m_discard_library_label->setString(Value(m_discard_library.size()).asString());
	}
	else {
		m_destory_library.pushBack(card);
	}
	return true;
}
bool CardLayer_::discard(bool isDestory) {
	if (m_hand_cards.size() == 0)	return false;
	return discardAtID(( rand() * 101) % m_hand_cards.size(), isDestory );
}
void CardLayer_::discardAll(bool isDestory) {
	while (discard(isDestory)) {

	}
}


bool CardLayer_::drawFromDisLibraryToHand() {
	if (m_discard_library.size() == 0) {
		return false;
	}
	return drawFromDisLibraryToHandAtID((rand() * 101) % m_discard_library.size());
}
bool CardLayer_::drawFromDisLibraryToHand(int num) {
	if (num == 0) {
		return true;
	}
	bool flag;
	for (int i = 0; i < num; i++) {
		flag = drawFromDisLibraryToHand();
	}
	return flag;
}
bool CardLayer_::drawFromDisLibraryToHandAtID(int index) {
	if (m_hand_cards.size() == MAX_HAND_CARD_NUM) {
		return false;
	}

	auto card = drawFromDisLibraryAtID(index);
	if (card == NULL) {
		return false;
	}

	m_hand_cards.pushBack(card);
	card->setPosition(m_dis_library_button->getPosition());
	card->setRotation(90 + rand() % 10);
	card->setScale(0);

	updateLayout();
	return true;

}
bool CardLayer_::drawFromDisLibraryToCardLibrary() {
	if (m_discard_library.size() == 0) {
		return false;
	}
	return drawFromDisLibraryToCardLibraryatID((rand() * 101) % m_discard_library.size());
}
bool CardLayer_::drawFromDisLibraryToCardLibraryatID(int index) {
	auto card = drawFromDisLibraryAtID(index);
	if (card == NULL) {
		return false;
	}

	m_card_library.pushBack(card);
	m_card_library_label->setString(Value(m_card_library.size()).asString());

	return true;
}



//目前的解决方案添加卡牌的时候就已经全部addChild了
//在适当的时候设为可见和不可见
bool CardLayer_::addCardToHandCard(BaseCard*& card) {
	if (m_hand_cards.size() == MAX_HAND_CARD_NUM) {	//如果等于卡牌上限则移入弃牌库
		addCardToDisLibrary(card);
		return false;
	}
	else {
		this->addChild(card);

		m_hand_cards.pushBack(card);	//把卡放进手牌中
		updateLayout();	//更新布局，并设为可见
		return true;
	}
}
void CardLayer_::addCardToCardLibrary(BaseCard*& card) {
	this->addChild(card);	//添加至父节点，设置为不可见
	card->setVisible(false);

	m_card_library.pushBack(card);
	m_card_library_label->setString(Value(m_card_library.size()).asString());
}
void CardLayer_::addCardToDisLibrary(BaseCard*& card) {
	this->addChild(card);	//添加至父节点，设置为不可见
	card->setVisible(false);

	m_discard_library.pushBack(card);
	m_discard_library_label->setString(Value(m_discard_library.size()).asString());
}


//更新布局函数
void CardLayer_::updateLayout() {
	clearLine();

	int card_num = m_hand_cards.size();
	if (card_num == 0)	return;

	int mid = card_num / 2;
	float space = m_visibleSize.width * touchableSize.width / (m_hand_cards.size() + 1) * card_num / MAX_HAND_CARD_NUM;

	for (int i = 0; i < card_num; i++) {
		BaseCard* card = m_hand_cards.at(i);
		card->stopAllActions();
		card->setVisible(true);	//把该卡设为可见

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
		//这是一个两次函数根据x计算y的
		float y = -2 * card->getContentSize().height / (m_visibleSize.width * touchableSize.width) / (m_visibleSize.width * touchableSize.width) * x * x +
			card->getContentSize().height * 3 / 7;

		card->runAction(Spawn::create(
			EaseInOut::create(MoveTo::create(0.2f, Vec2(x + m_visibleSize.width / 2, y)), 1.0f),
			ScaleTo::create(0.2f, 1.0f), NULL)
		);
		//card->runAction(ScaleTo::create(0.2f, 1.0f));
		//card->setPosition(x + m_visibleSize.width / 2, y);
		Vec2 rot = Vec2(x + m_visibleSize.width / 2, y) - Vec2(x_, -m_visibleSize.height / 3);
		//设置旋转角度
		if (i < mid && (90 - CC_RADIANS_TO_DEGREES(rot.getAngle())) != card->getRotation()) {
			card->runAction(RotateTo::create(0.2f, 90 - CC_RADIANS_TO_DEGREES(rot.getAngle())));
			//card->setRotation(CC_RADIANS_TO_DEGREES(rot.getAngle() - 90));
		}
		else if ((90 - CC_RADIANS_TO_DEGREES(rot.getAngle())) != card->getRotation()) {
			card->runAction(RotateTo::create(0.2f, 90 - CC_RADIANS_TO_DEGREES(rot.getAngle())));
			//card->setRotation(90 - CC_RADIANS_TO_DEGREES(rot.getAngle()));
		}
	}
}
void CardLayer_::checkCardLibrary(Ref* pSender) {
	Vector<BaseCard*> cards;
	if (((Node*)pSender)->getName() == "card_library_button") {
		for (BaseCard* card : m_card_library) {
			cards.pushBack(CardSystem::createCardByID(card->getCardID()));
		}
	}
	else {
		for (BaseCard* card : m_discard_library) {
			cards.pushBack(CardSystem::createCardByID(card->getCardID()));
		}
	}

	Layer* card_display_layer;
	card_display_layer = CardDisplayLayer::create(cards);
	this->addChild(card_display_layer, 103);
}

//void CardLayer_::useCard() {
//	//从手牌中移除卡牌，并设为不可见
//	m_hand_cards.eraseObject(m_current_card);
//	m_discard_library.pushBack(m_current_card);
//	m_current_card->setVisible(false);
//}

void CardLayer_::update(float dt) {
	for (int i = 0; i < m_hand_cards.size(); i++) {
		BaseCard* card = m_hand_cards.at(i);
		if (card != m_current_card) {
			card->setScale(1.0f);
			card->setZOrder(i);
		}
	}
}

bool CardLayer_::onTouchBegan(Touch* pTouch, Event* pEvent) {
	if (!m_isSendCard) {
		CCLOG("CARDLAYER-TOUCH");
		if (m_isHovor) {
			m_isSelect = true;
			return true;
		}
		else {
			return false;
		}
	}
}
void CardLayer_::onTouchMoved(Touch* pTouch, Event* pEvent) {
	if (!m_isSendCard) {
		if (m_isCurrentCanMove) {
			m_current_card->setPosition(pTouch->getLocation());
		}
	}
}
void CardLayer_::onTouchEnded(Touch* pTouch, Event* pEvent) {
	if (!m_isSendCard) {
		CCLOG("CARDLAYER-TOUCH-END");
		if (pTouch->getLocation().y > m_visibleSize.height * touchableSize.height) {
			//驱动卡牌进行effect
			auto scene = (GameSceneDemo*)getParent();
			Target target = scene->getTarget(m_current_card);	//从父节点获取Target
			if (target.isReady) {
				//先从手牌中去除
				m_hand_cards.eraseObject(m_current_card);
				m_discard_library.pushBack(m_current_card);
				m_discard_library_label->setString(Value(m_discard_library.size()).asString());

				if (m_current_card->m_target_need.enemy_need == 1) {
					// 线清空
					clearLine();
					// 设置卡牌处于发送状态,卡牌发送过程中暂停其他一切对卡牌区的事件响应...
					m_isSendCard = true;
					//曲线配置  
					ccBezierConfig cfg;
					cfg.controlPoint_1 = control1;
					cfg.controlPoint_2 = control2;
					cfg.endPosition = endPoint;

					m_current_card->runAction(CCSequence::create(
						CCSpawn::create(
							CCScaleTo::create(0.5, 0.2), CCEaseInOut::create(CCBezierTo::create(0.5, cfg), 0.5), NULL),
						//CCCallFunc::create(this, callfunc_selector(CardLayer_::callfunc)),
						CCCallFuncN::create(std::bind(&CardLayer_::callfunc, this, m_current_card, target)),
						NULL));
					return;
				}
				m_current_card->setVisible(false);
				m_current_card->effect(target);
			}
		}
		updateLayout();
		m_isHovor = false;
		m_isSelect = false;
		m_current_card = NULL;
	}
}

// 对于动作回调函数，不能直接调用类成员的函数（但是可以对类成员赋值），而是把类成员作为参数传递进来.
void CardLayer_::callfunc(BaseCard * card, Target target) {
	card->setVisible(false);
	card->effect(target);

	auto scene = (GameSceneDemo*)(getParent());
	scene->play_music("audio/effect/attack.ogg");
	scene->explode_on_enemy(target);

	updateLayout();
	m_isHovor = false;
	m_isSelect = false;
	m_current_card = NULL;
	m_isSendCard = false;
}

void CardLayer_::enemy_shake_action_callback() {
	m_isEnemyCanShake = true;
}

// 获得贝塞尔曲线的坐标点 ... 
Vec2* CardLayer_::getCubicBezierPoints(const Vec2 &origin, const Vec2 &control1,
	const Vec2 &control2, const Vec2 &destination, unsigned int segments) {
	Vec2* vertices = new (std::nothrow) Vec2[segments + 1];
	if (!vertices)
		return nullptr;

	float t = 0;
	for (unsigned int i = 0; i < segments; i++)
	{
		vertices[i].x = powf(1 - t, 3) * origin.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * destination.x;
		vertices[i].y = powf(1 - t, 3) * origin.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * destination.y;
		t += 1.0f / segments;
	}
	vertices[segments].x = destination.x;
	vertices[segments].y = destination.y;
	return vertices;
}

void CardLayer_::onMouseMove(EventMouse* pEvent) {
	if (!m_isSendCard) {
		if (!m_isSelect) {
			b2AABB touchAABB;	//触碰点AABB
			touchAABB.lowerBound.Set(pEvent->getCursorX() / PTM_RATIO - 0.0001, pEvent->getCursorY() / PTM_RATIO - 0.0001);
			touchAABB.upperBound.Set(pEvent->getCursorX() / PTM_RATIO + 0.0001, pEvent->getCursorY() / PTM_RATIO + 0.0001);

			for (int i = m_hand_cards.size() - 1; i >= 0; i--) {
				BaseCard* card = m_hand_cards.at(i);
				if (card->getBody()->GetFixtureList()->GetAABB(0).Contains(touchAABB)) {
					auto scene = (GameSceneDemo*)(getParent());
					card->setScale(1.25f);
					card->setZOrder(10);
					m_current_card = card;
					if (m_oldSelectCard != m_current_card) {
						scene->play_music("audio/effect/CardSelect.ogg");
						m_oldSelectCard = m_current_card;
					}
					if (m_current_card->m_target_need.enemy_need == 1) m_isCurrentCanMove = false;
					else m_isCurrentCanMove = true;
					m_isHovor = true;
					return;
				}
			}
			m_current_card = NULL;
			m_oldSelectCard = NULL;
			m_isHovor = false;
			return;
		}
		else {
			if (m_current_card->m_target_need.enemy_need == 1) {
				Vec2 startPoint = m_current_card->getPosition();
				endPoint = Vec2(pEvent->getCursorX(), pEvent->getCursorY());
				control1 = ((endPoint - startPoint) * 0.3 + startPoint);
				control2 = ((endPoint - startPoint) * 0.7 + startPoint);
				control1.y = control1.y * 1.5;
				control2.y = control2.y * 1.5;

				Vec2 normal = Vec2(0.0, 1.0);
				float var = 180.0f / 3.14f;
				Vec2 * points = getCubicBezierPoints(startPoint, control1, control2, endPoint, LINE_SPRITE_NUMBER);
				for (int i = 0; i < LINE_SPRITE_NUMBER; i++) {
					line[i]->setPosition(points[i]);
					line[i]->setScale( (i+1) * 0.09 );
					if (i > 0) {
						Vec2 v = points[i] - points[i - 1];
						float cos = v.dot(normal) / (v.length()*normal.length());
						float theta = acos(cos) * var;
						if (v.x < 0) line[i]->setRotation(-theta);
						else line[i]->setRotation(theta);
					}
					line[i]->setVisible(true);
				}
				CC_SAFE_DELETE_ARRAY(points);
				
				auto scene = (GameSceneDemo*)(getParent());
				for (BaseEnemy * enemy : scene->m_enemys) {
					if (enemy->getBoundingBox().containsPoint(endPoint)) {
						for (int i = 0; i < LINE_SPRITE_NUMBER; i++) {
							line[i]->setColor(Color3B::RED);
						}

						scene->m_current_enemy = enemy;
						if (m_isEnemyCanShake) {
							enemy->runAction(CCSequence::create(
								CCShake::create(0.5, 10), CCCallFuncN::create
								(std::bind(&CardLayer_::enemy_shake_action_callback, this)),
								NULL));
							m_isEnemyCanShake = false;
						}
						return;
					}
				}
				for (int i = 0; i < LINE_SPRITE_NUMBER; i++) {
					line[i]->setColor(Color3B::GRAY);
				}
				scene->m_current_enemy = NULL;
			}
			else {
				clearLine();
			}
		}
	}
}

void CardLayer_::effect_when_round_end() {
	this->discardAll(false);
	for (int i = 0; i < m_draw_when_round_end; i++) {
		drawCard();
	}
}