#pragma once

#ifndef _DEMO_SCENE_H_
#define _DEMO_SCENE_H_

#include"GameConfig.h"

#include"BaseCard.h"
#include"Player.h"
#include"BaseEnemy.h"

#include"StateHeader.h"
#include"EffectHeader.h"

#include"BaseLibrary.h"

#include"sqlite3\sqlite3.h"	//测试sqlite3是否可用

#include"ui\CocosGUI.h"
using namespace cocos2d::ui;

//测试场景，用于测试各种各样的东西是否可以运行
class DemoScene :public Layer {
public:
	static Scene* createScene();

	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(DemoScene);

	void testFunction( Ref* pSender, Widget::TouchEventType event );

private:

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

private:
	Size visibleSize;

	BaseCard * baseCard;

	Player* player;
	BaseEnemy* enemy;

	BaseLibrary* library;

	PropertyChangeState* powerState;
	//HandCardLayer* m_handCard;


	//sqlite3* pdb;	//测试数据库
};


//int callback(void* para, int col_num, char** col_value, char** col_name);
#endif // !_DEMO_SCENE_H_
