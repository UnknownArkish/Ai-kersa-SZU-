#pragma once

#ifndef _TEST_CARD_LAYER_H_
#define _TEST_CARD_LAYER_H_

#include"GameConfig.h"
class TestCardLayer : public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(TestCardLayer);
private:

	virtual bool init();
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* pEvent);

private:
	//CardLayer_* m_cardLayer;
};

#endif // !_TEST_CARD_LAYER_H_
