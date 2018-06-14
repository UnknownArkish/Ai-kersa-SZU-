#pragma once

#ifndef _TARGET_H_
#define _TARGET_H_

#include"GameConfig.h"
#include"Player.h"
#include"BaseEnemy.h"

enum TargetType {
	TO_PLAYER,
	TO_ENEMY,
	TO_CARD_LAYER
};

struct Target {
	bool isReady = false;

	Vector<Player*> players;
	Vector<BaseEnemy*> enemys;
	Vector<Layer*> cardLayers;
};
struct TargetNeed {
	int player_need = 0;
	int enemy_need = 0;
	int card_layer_need = 0;
};

#endif // !_TARGET_H_
