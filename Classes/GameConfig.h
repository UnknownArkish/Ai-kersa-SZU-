#pragma once

#ifndef _GAME_CONFIG_H_
#define _GAME_CONFIG_H_

#include"cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

static const cocos2d::Size designResolutionSize = cocos2d::Size(1600, 900);
static const Size touchableSize = cocos2d::Size(0.7, 0.4);
static const Size card_display_size = cocos2d::Size(0.8, 0.45);

#define PTM_RATIO 32
#define MAX_HAND_CARD_NUM 9
#define INIT_HAND_CARD_NUM 5

#define NUM_OF_CARD_DISPLAY_PER_ROW 3

#define MSG_PLAYER_PROPERTY_CHANGE "msg_player_property_change"

#endif // !_GAME_CONFIG_H_
