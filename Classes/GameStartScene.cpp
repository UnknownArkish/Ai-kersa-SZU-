#include"GameStartScene.h"
#include"GameSceneDemo.h"

Scene* GameStartScene::createScene() {
	Scene* scene = Scene::create();
	Layer* layer = GameStartScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameStartScene::init() {
	if (!Layer::init()) {
		return false;
	}
	Vec2 origin = _director->getVisibleOrigin();
	Size visibleSize = _director->getVisibleSize();

	Texture2D* texture = _director->getTextureCache()->addImage("background/start_background_blur.png");

	m_background = Sprite::create("background/start_background_blur.png");
	m_background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	float scale = visibleSize.width / texture->getContentSize().width;
	m_background->setScale(scale);
	this->addChild(m_background , 0);

	LayerColor* mask_layer = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
	mask_layer->runAction( EaseSineOut::create( FadeOut::create(3.8f) ));
	this->addChild(mask_layer , 3);

	m_logo = Sprite::create("background/logo.png");
	m_logo->setPosition(m_background->getPositionX(), visibleSize.height * 8 / 13);
	m_logo->setScale(scale);
	this->addChild(m_logo, 5);

	MenuItemFont::setFontSize(86);
	MenuItemFont::setFontName("fonts/LetterGothicStd.otf");
	MenuItemFont* start_item = MenuItemFont::create( "Start" , CC_CALLBACK_1(GameStartScene::menuItemCallback, this) );
	start_item->setPositionY( -visibleSize.height / 2 +  visibleSize.height * 6 / 14);
	start_item->setTag(100);
	MenuItemFont* exit_item = MenuItemFont::create("Exit", CC_CALLBACK_1(GameStartScene::menuItemCallback, this));
	exit_item->setPositionY(-visibleSize.height / 2 + visibleSize.height * 4 / 14);
	exit_item->setTag(101);

	Menu* menu = Menu::create(start_item, exit_item, NULL);
	this->addChild(menu);

	return true;
}

void GameStartScene::menuItemCallback(Ref* pSender) {
	MenuItemFont* item = (MenuItemFont*)pSender;
	switch (item->getTag()) {
	case 100:
		_director->replaceScene(GameSceneDemo::createScene());
		break;
	case 101:
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
				MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
				return;
		#endif

		Director::getInstance()->end();//windows平台和安卓主要调用这一句

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				exit(0);
		#endif
		break;
	}
}

void GameStartScene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bgm.mp3" , true);
}
void GameStartScene::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}