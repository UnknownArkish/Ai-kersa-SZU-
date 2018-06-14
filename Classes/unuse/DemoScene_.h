#pragma once

#ifndef _DEMO_SCENE__H_
#define _DEMO_SCENE__H_

#include"GameConfig.h"
#include"CardSystem.h"
#include"BaseLibrary.h"
#include"BaseCard.h"

class DemoScene_ :public Layer {
public:
	static Scene* createScene();

private:
	CREATE_FUNC(DemoScene_);
	virtual bool init();

	virtual void update(float dt);

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

private:
	Size m_visiableVize;
	BaseLibrary* library;

	BaseCard* card;
	bool m_flag;
};

#endif // !_DEMO_SCENE__H_
