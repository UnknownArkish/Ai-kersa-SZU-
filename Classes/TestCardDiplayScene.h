#pragma once

#ifndef _CARD_DISPLAY_SCENE_H_
#define _CARD_DISPLAY_SCENE_H_

#include"GameConfig.h"

class TestCardDisplayScene : public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(TestCardDisplayScene);
private:
	virtual bool init();
};

#endif // !_CARD_DISPLAY_SCENE
