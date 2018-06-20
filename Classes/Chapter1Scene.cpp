#include"Chapter1Scene.h"
#include"GameStartScene.h"
#include"GameSceneDemo.h"

Scene* Chapter1Scene::createScene() {
	Scene* scene = Scene::create();
	Layer* layer = Chapter1Scene::create();
	scene->addChild(layer);
	return scene;
}

bool Chapter1Scene::init() {
	if (!DialogScene::init("chapter1")) {
		return false;
	}
	return true;
}

void Chapter1Scene::endDialogScene(Ref* ref) {
	//ÇÐ»»³¡¾°
	auto func = [&]() {
		CCLOG("Replacing Scene...");
		Director::getInstance()->replaceScene(GameSceneDemo::createScene());	//Ìæ»»³ÉÓÎÏ·³¡¾°
	};
	m_mask_layer->runAction(Sequence::create(FadeIn::create(1.0f),/* DelayTime::create(0.2f),*/ CallFunc::create(func), NULL));
}
void Chapter1Scene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/chapter0_bgm.mp3", true);
}
void Chapter1Scene::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}