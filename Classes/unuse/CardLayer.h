#pragma once

#ifndef _CARD_LAYER_H_
#define _CARD_LAYER_H_

#include"GameConfig.h"
#include"BaseLibrary.h"
#include"BaseCard.h"

class CardLayer :public Layer {
public:
	static CardLayer* create( std::vector<CardID>& cardIDs );

	bool addCardToHand(BaseCard*& card);
	void addCardToCardLibrary(BaseCard*& card);
	void addCardToDisLibrary(BaseCard*& card);

	bool drawCard();	//从抽牌库中抽牌
	bool drawFromDisLibraryToHand();	//（随机）从弃牌库中抽牌放回手牌
	bool drawFromDisLibraryToCardLibrary();	//（随机）从弃牌库中抽牌放回抽牌库

	int getSizeOfHandCard() { return m_hand_cards.size(); }
	int getSizeOfCardLibrary() { return m_card_library->getLibrarySize(); }
	int getSizeOfDiscardLibrary() { return m_discard_library->getLibrarySize(); }

private:
	void updateLayout();	//更新布局

	virtual bool init( std::vector<CardID>& cardIDs );
	virtual void update(float dt);

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

	virtual void onMouseMove(EventMouse* pEvent);	//用于检测鼠标停放在卡牌贴图上时的函数

private:
	Size m_visibleSize;

	BaseLibrary * m_card_library;
	BaseLibrary* m_discard_library;

	Vector<BaseCard*> m_hand_cards;
	BaseCard* m_current_card;

	bool m_isHovor;	//是否悬浮在手牌上
	bool m_isSelect;	//是否选择了一张卡牌

};

#endif // !_CARD_LAYER_H_

