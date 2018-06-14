#pragma once

#ifndef _AI_MANAGER_H_
#define _AI_MANAGER_H_

#include"GameConfig.h"
#include"BaseEnemy.h"
#include"Player.h"

class AIManager :public Node {
public:
	static AIManager* create( Player* player , Vector<BaseEnemy*> enemys );

	void addEnemy(BaseEnemy* enemy) { m_enemys.pushBack(enemy); }
	void removeEnemy(BaseEnemy* enemy) { m_enemys.eraseObject(enemy); }

	void effect_when_round_end( int round );
private:
	virtual bool init(Player* player, Vector<BaseEnemy*> enemy);

	void createIntent(int round);
private:
	Player * m_player;
	Vector<BaseEnemy*> m_enemys;
};

#endif // !_AI_MANAGER_H_
