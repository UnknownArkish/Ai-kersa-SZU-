#pragma once

#ifndef _HAND_CARD_LAYER
#define _HAND_CARD_LAYER

#include"GameConfig.h"
#include"BaseCard.h"
#include"vector"

//这个类意义不大，因为不通用
class HandCardLayer:public Layer {
public:
	static HandCardLayer * create(int cardNum);

private:
	virtual bool init( int cardNum );
	virtual void update(float dt);

	void onMouseMove(EventMouse* pEvent);

private:
	bool m_isHover;

	BaseCard * m_currentCard;

	Vector<BaseCard*> m_handCardList;
};


#endif // !_HAND_CARD_LAYER

