#pragma once

#ifndef _CARD_LAYER__H_
#define _CARD_LAYER__H_

#include"GameConfig.h"
#include"BaseCard.h"
#include"CardSystem.h"

class CardLayer_ :public Layer {
public:
	static CardLayer_* create(std::vector<CardID>& cardIDs);


	BaseCard* drawFromCardLibrary();	//从抽牌库获取卡牌
	BaseCard* drawFromCardLibraryAtID(int index);	//从下标为index的抽牌库抽取卡牌
	BaseCard* drawFromDisLibrary();	//从弃牌库获取卡牌
	BaseCard* drawFromDisLibraryAtID( int index );	//从下标为index的弃牌库抽取卡牌

	bool drawCard();	//从牌库中抽取卡牌
	bool drawCard(int num);	//抽牌库中抽取num张卡牌
	bool drawCardAtID(int index);
	void drawFull();

	bool discard( bool isDestory );	//随机丢弃手牌
	bool discardAtID(int index , bool isDestory);	//丢弃手牌
	void discardAll( bool isDestory );	//丢弃所有手牌

	bool drawFromDisLibraryToHand();	//（随机）从弃牌库中抽取卡牌到手牌
	bool drawFromDisLibraryToHand( int num );	//（随机）从弃牌库中抽取num张卡牌到手牌
	bool drawFromDisLibraryToCardLibrary();	//（随机）从弃牌库中抽取卡牌到抽牌库
	bool drawFromDisLibraryToHandAtID( int index );	//（随机）从弃牌库中抽取卡牌到手牌
	bool drawFromDisLibraryToCardLibraryatID( int index );	//（随机）从弃牌库中抽取卡牌到抽牌库

	bool addCardToHandCard(BaseCard*& card);	//额外增加卡牌的函数
	void addCardToCardLibrary(BaseCard*& card);
	void addCardToDisLibrary(BaseCard*& card);

	int getSizeOfCardLibrary() { return m_card_library.size(); }
	int getSizeOfHandCard() { return m_hand_cards.size(); }
	int getSizeOfDisLibrary() { return m_discard_library.size(); }

	bool getIsSelect() { return m_isSelect; }

	void effect_when_round_end();
private:
	void updateLayout();	//更新布局
	void checkCardLibrary(Ref* pSender);
	//void useCard();

	virtual bool init(std::vector<CardID> cardIDs);
	virtual void update(float dt);

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

	virtual void onMouseMove(EventMouse* pEvent);	//用于检测鼠标停放在卡牌贴图上时的函数
private:
	Size m_visibleSize;

	MenuItemImage* m_card_library_button;	//抽牌库精灵
	Label* m_card_library_label;	//抽牌库剩余卡牌数
	MenuItemImage* m_dis_library_button;	//弃牌库精灵
	Label* m_discard_library_label;	//弃牌库剩余卡牌数

	Vector<BaseCard*> m_card_library;	//抽牌库
	Vector<BaseCard*> m_discard_library;	//弃牌库
	Vector<BaseCard*> m_hand_cards;	//手牌库

	Vector<BaseCard*> m_destory_library;	//摧毁的牌库

	BaseCard* m_current_card;	//当前选择卡牌

	int m_draw_when_round_end = 2;	//结束时抽取卡牌数，对牌库作用的Effect可以对这个产生影响，从而改变每回合抽牌数

	bool m_isHovor;	//是否悬浮
	bool m_isSelect;	//是否选择了一张卡牌

};

#include"GameSceneDemo.h"
#endif // !_CARD_LAYER__H_