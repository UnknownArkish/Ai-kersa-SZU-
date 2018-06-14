#pragma once

#ifndef _GAME_SCENE_DEMO_H_
#define _GAME_SCENE_DEMO_H_

#include"GameConfig.h"

#include"BaseCard.h"

#include"Player.h"
#include"BaseEnemy.h"
#include"Target.h"

#include"CardLayer_.h"

#include"BaseBehaviour.h"

#include"AIManager.h"


class GameSceneDemo :public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(GameSceneDemo);

	Target getTarget(BaseCard* card);	//根据卡牌返回Target
	Target getTarget(BaseBehaviour* behaviour);	//根据TargetNeed返回Target
	int getCurrentRound() { return m_current_rounds; }
private:
	void endRound( Ref* pRef );
	void updateCostLabel();

	virtual bool init();
	virtual void update(float dt);

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

	virtual void onMouseMove(EventMouse* pEvent);	//用于检测鼠标停放在敌人贴图上时的函数
private:
	int m_current_rounds;

	Size m_visibleSize;

	CardLayer_* m_card_layer;

	Player * m_player;
	Vector<BaseEnemy*> m_enemys;
	BaseEnemy* m_current_enemy;	//保存当前目标对象

	AIManager* m_ai_manager;

	Label* m_cost_label;
};

#endif // !_GAME_SCENE_DEMO_H_
