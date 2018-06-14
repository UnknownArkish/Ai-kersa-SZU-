#include"DrawCardEffect.h"
#include"CardLayer_.h"

DrawCardEffect* DrawCardEffect::create( TargetType type ,  int draw_num, DrawFrom from) {
	DrawCardEffect* pRet = new(std::nothrow)DrawCardEffect();
	if (pRet && pRet->init(type ,draw_num, from)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool DrawCardEffect::init( TargetType type , int draw_num, DrawFrom from ) {
	if (!BaseEffect::init(type)) {
		return false;
	}
	m_draw_num = draw_num;
	m_from = from;

	return true;
}

void DrawCardEffect::effect(Target& target) {
	auto cardLayer = (CardLayer_*)target.cardLayers.at(0);	//»ñÈ¡¿¨ÅÆLayer
	switch (m_from) {
		case DrawFrom::From_Card_Library:
			if (m_draw_num >= 0) {
				cardLayer->drawCard(m_draw_num);
			}
			else {
				cardLayer->drawFull();
			}
			break;
		case DrawFrom::From_Dis_Library:
			if (m_draw_num >= 0) {
				cardLayer->drawFromDisLibraryToHand(m_draw_num);
			}
			break;
	}
}