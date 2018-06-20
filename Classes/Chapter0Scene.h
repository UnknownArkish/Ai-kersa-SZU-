#pragma once

#ifndef _CHAPTER_0_H_
#define _CHAPTER_0_H_

#include"DialogScene.h"
#include"GameConfig.h"

class Chapter0Scene : public DialogScene {
public:
	static Scene* createScene();
	CREATE_FUNC(Chapter0Scene);

private:
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

	virtual void endDialogScene(Ref* ref);
};


#endif // !_CHAPTER_0_H_
