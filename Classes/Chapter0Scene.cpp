#include"Chapter0Scene.h"
#include"GameStartScene.h"
#include"Chapter1Scene.h"

Scene* Chapter0Scene::createScene() {
	Scene* scene = Scene::create();
	Layer* layer = Chapter0Scene::create();
	scene->addChild(layer);
	return scene;
}

bool Chapter0Scene::init() {
	if (!DialogScene::init("chapter0")) {
		return false;
	}
	return true;
}

void Chapter0Scene::endDialogScene(Ref* ref) {
	//ÇÐ»»³¡¾°
	auto func = [&]() {
		CCLOG("Replacing Scene...");
		Director::getInstance()->replaceScene(Chapter1Scene::createScene());
	};
	m_mask_layer->runAction(Sequence::create(FadeIn::create(1.0f),/* DelayTime::create(0.2f),*/ CallFunc::create(func), NULL));
}

void Chapter0Scene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/chapter0_bgm.mp3", true);
}
void Chapter0Scene::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}