#include"CardDisplayLayer.h"

CardDisplayLayer* CardDisplayLayer::create(Vector<BaseCard*> cards) {
	CardDisplayLayer* pRet = new(std::nothrow)CardDisplayLayer();
	if (pRet  && pRet->init(cards)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
bool CardDisplayLayer::init(Vector<BaseCard*> cards) {
	if (  !Layer::init()) {
		return false;
	}
	auto visibleSize = _director->getVisibleSize();

	m_cards = cards;
	
	m_scrollView_visibleSize = Size(visibleSize.width * card_display_size.width, visibleSize.height * card_display_size.height);

	auto color_layer = LayerColor::create(Color4B(255, 255, 255, 120));
	this->addChild(color_layer);

	Layer* container = Layer::create();
	Size containerSize = Size(220 * m_cards.size(), 300);
	container->setContentSize(containerSize);

	for (int i = 0; i < cards.size(); i++) {
		auto card = m_cards.at(i);
		card->setAnchorPoint(Vec2::ZERO);
		card->setPosition( card->getContentSize().width / 2 + i * 220 , card->getContentSize().height / 2 );
		container->addChild(card);
	}
	ScrollView* scrollView = ScrollView::create(m_scrollView_visibleSize , container);
	scrollView->setPosition(visibleSize.width * (1 - card_display_size.width) / 2, visibleSize.height * (1 - card_display_size.height) / 2);
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->setBounceable(true);        //是否具有弹性
	scrollView->setDelegate(this);
	this->addChild(scrollView , 10 , 5);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);	//吞噬触摸事件
	listener->onTouchBegan = CC_CALLBACK_2(CardDisplayLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool CardDisplayLayer::onTouchBegan(Touch* pTouch, Event* pEvent) {
	auto scrollableRect = Rect( this->getChildByTag(5)->getPosition() , m_scrollView_visibleSize );
	if ( !scrollableRect.containsPoint(pTouch->getLocation()) ) {
		this->removeFromParent();
	}
	return false;
}

void CardDisplayLayer::scrollViewDidScroll(ScrollView* view)
{
	CCLOG("ScrollView Moved!");
}
void CardDisplayLayer::scrollViewDidZoom(ScrollView* view)
{
	CCLOG("ScrollView Scaled");
}