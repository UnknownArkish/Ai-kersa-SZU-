#pragma once

#ifndef _CARD_SYSTEM_H_
#define _CARD_SYSTEM_H_

#include"GameConfig.h"
#include"BaseCard.h"
#include"sqlite3\sqlite3.h"
#include"Box2D\Box2D.h"

class CardSystem {
public:
	static BaseCard* createCardByID(CardID id);
private:
	static b2World * m_world;
};
#endif // !_CARD_SYSTEM_H_
