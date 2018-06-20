#pragma once

#ifndef _CHAPTER_1_H_
#define _CHAPTER_1_H_

#include"DialogScene.h"
#include"GameConfig.h"

class Chapter1Scene : public DialogScene {
public:
	static Scene* createScene();
	CREATE_FUNC(Chapter1Scene);

private:
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

	virtual void endDialogScene(Ref* ref);
};


#endif // !_CHAPTER_1_H_
