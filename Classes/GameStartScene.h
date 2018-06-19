#pragma once

#ifndef _GAME_START_SCENE_H_
#define _GAME_START_SCENE_H_

#include"GameConfig.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;

class GameStartScene :public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(GameStartScene);

private:
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

	void menuItemCallback(Ref* pSender);
private:
	Sprite * m_background;
	Sprite * m_logo;
	LayerColor* m_mask_layer;
};


#endif // !_GAME_START_SCENE_H_
