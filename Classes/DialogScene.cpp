#include"DialogScene.h"
#include"sqlite3\sqlite3.h"
#include"GameStartScene.h"

//Scene* DialogScene::createScene(std::string dialog_form_name) {
//	Scene* scene = Scene::create();
//	Layer* layer = DialogScene::create(dialog_form_name);
//	scene->addChild(layer);
//	return scene;
//}
//Scene* DialogScene::createScene() {
//	Scene* scene = Scene::create();
//	Layer* layer = DialogScene::create("dialog_demo");
//	scene->addChild(layer);
//	return scene;
//}
//
//DialogScene* DialogScene::create(std::string dialog_form_name) {
//	DialogScene* pRet = new(std::nothrow)DialogScene();
//	if (pRet && pRet->init(dialog_form_name)) {
//		pRet->autorelease();
//		return pRet;
//	}
//	else {
//		delete pRet;
//		pRet = NULL;
//		return NULL;
//	}
//}

bool DialogScene::init( std::string dialog_form_name ) {
	if (!Layer::init()) {
		return false;
	}
	//从指定表中读取数据
	if (!this->initDialogFromSQL(dialog_form_name)) {
		return false;
	}
	m_visibleSize = _director->getVisibleSize();

	//初始化背景图位置
	m_pre_background_picPath = m_background_picPaths.at(0);
	m_background_sprite = Sprite::create(m_pre_background_picPath);
	float xScale = m_visibleSize.width / m_background_sprite->getContentSize().width;
	float yScale = m_visibleSize.height / m_background_sprite->getContentSize().height;
	m_background_sprite->setScale(xScale > yScale ? xScale : yScale);
	m_background_sprite->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
	this->addChild(m_background_sprite);

	//初始化人物位置
	m_pre_character_picPath = m_character_picPaths.at(0);
	m_character_sprite = Sprite::create(m_pre_character_picPath);
	Size character_size = Size(m_visibleSize.width * dialog_character_size.width, m_visibleSize.height * dialog_character_size.height);
	xScale = character_size.width / m_character_sprite->getContentSize().width;
	yScale = character_size.height / m_character_sprite->getContentSize().height;
	m_character_sprite->setScale(xScale > yScale ? xScale: yScale);
	m_character_sprite->setPosition( m_visibleSize.width * 0.372, m_visibleSize.height * 5 / 13);
	this->addChild(m_character_sprite);

	//初始化对话框白色透明背景
	LayerColor* dialog_color_layer = LayerColor::create( Color4B(255, 255, 255, 160), 
		m_visibleSize.width * dialog_dialog_size.width, m_visibleSize.height * dialog_dialog_size.height);
	dialog_color_layer->setPosition(
		-dialog_color_layer->getContentSize().width / 2 + m_visibleSize.width / 2  , 
		- dialog_color_layer->getContentSize().height/2 +  m_visibleSize.height / 2 * 0.382);
	dialog_color_layer->setTag(TAG_DIALOG_COLOR_LAYER);
	this->addChild(dialog_color_layer);

	//初始化对话Label
	m_dialog_label = Label::create( m_dialogs.at(0) ,"Arical" , 32);
	m_dialog_label->setColor(Color3B( 60 , 64 , 108 ));
	m_dialog_label->setPosition(dialog_color_layer->getContentSize().width / 2, dialog_color_layer->getContentSize().height * 10.6 / 13);
	m_dialog_label->setAnchorPoint(Point(0.5f, 1.0f));
	m_dialog_label->setWidth(dialog_color_layer->getContentSize().width * 11 / 13);
	m_dialog_label->setLineBreakWithoutSpace(true);
	m_dialog_label->setAlignment(CCTextAlignment::LEFT);
	dialog_color_layer->addChild(m_dialog_label);

	MenuItemFont::setFontSize(48);
	MenuItemFont::setFontName("fonts/LetterGothicStd.otf");
	MenuItemFont* skip_item = MenuItemFont::create("Skip", CC_CALLBACK_1(DialogScene::endDialogScene, this));
	skip_item->setColor(Color3B::WHITE);
	skip_item->setPosition( -m_visibleSize.width /2 -skip_item->getContentSize().width / 2 + dialog_color_layer->getPositionX() +  dialog_color_layer->getContentSize().width, 
		-m_visibleSize.height/2 + skip_item->getContentSize().height / 2 + dialog_color_layer->getPositionY() + dialog_color_layer->getContentSize().height);
	Menu* menu = Menu::create(skip_item,NULL);
	this->addChild(menu);

	//初始化名字白色透明背景
	LayerColor* name_color_layer = LayerColor::create(Color4B(255, 255, 255, 200), 
		m_visibleSize.width * dialog_name_size.width, m_visibleSize.height * dialog_name_size.height);
	name_color_layer->setPosition(
		-name_color_layer->getContentSize().width / 2 * 0.618f , 
		-name_color_layer->getContentSize().height/2  + dialog_color_layer->getContentSize().height);
	dialog_color_layer->setTag(TAG_NAME_COLOR_LAYER);
	dialog_color_layer->addChild(name_color_layer);

	//初始化名字Label
	m_pre_name = m_names.at(0);
	m_name_label = Label::create(m_pre_name, "Arical", 36);
	m_name_label->setColor(Color3B(48, 48, 84));
	m_name_label->setPosition( name_color_layer->getContentSize().width * 0.382 , name_color_layer->getContentSize().height / 2);
	name_color_layer->addChild(m_name_label);


	//初始化遮罩层
	m_mask_layer = LayerColor::create(Color4B::WHITE, m_visibleSize.width, m_visibleSize.height);
	m_mask_layer->runAction(EaseSineOut::create(FadeOut::create(1.0f)));
	this->addChild(m_mask_layer);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(DialogScene::onTouchBegan , this);
	listener->onTouchEnded = CC_CALLBACK_2(DialogScene::onTouchEnded , this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool DialogScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
	if (m_is_dialog_showing) {
		m_is_dialog_showing = false;
		return false;
	}
	return true;
}
void DialogScene::onTouchEnded(Touch* pTouch, Event* pEvent) {
	m_counter++;
	if (m_counter >= m_background_picPaths.size()) {
		endDialogScene(this);
		return;
	}
	
	//更新背景
	if ( m_pre_background_picPath != m_background_picPaths.at(m_counter)) {
		m_pre_background_picPath = m_background_picPaths.at(m_counter);
		auto func = [&]() {
			Texture2D* texture = Director::getInstance()->getTextureCache()->getTextureForKey(m_background_picPaths.at(m_counter));
			m_background_sprite->setTexture(texture);	//更换贴图
		};
		m_mask_layer->runAction( Sequence::create(FadeIn::create(1.0f) ,CallFunc::create(func), FadeOut::create(1.0f) , NULL ));

	}

	//更新人物
	if (m_pre_character_picPath != m_character_picPaths.at(m_counter)) {
		m_pre_character_picPath = m_character_picPaths.at(m_counter);

		auto func = [&]() {
			Texture2D* texture = Director::getInstance()->getTextureCache()->getTextureForKey(m_character_picPaths.at(m_counter));
			m_character_sprite->setTexture(texture);
		};
		m_character_sprite->runAction(Sequence::create(FadeOut::create(0.18f), CallFunc::create(func), FadeIn::create(0.30f), NULL));	
	}

	//更新名字
	if (m_pre_name != m_names.at(m_counter)) {
		m_pre_name = m_names.at(m_counter);

		m_name_label->setString(m_names.at(m_counter));
	}

	//更新Dialog
	m_n = 0;
	m_is_dialog_showing = true;
	m_dialog_label->runAction( RepeatForever::create(
		Sequence::create( CallFunc::create( CC_CALLBACK_0( DialogScene::toUpdateDialog,this) ) , DelayTime::create(0.025f) , NULL ) 
	) );
}

void DialogScene::toUpdateDialog() {
	std::string dialog = m_dialogs.at(m_counter);
	if (m_n > dialog.size() ) {
		m_dialog_label->setString(dialog);
		m_dialog_label->stopAllActions();
		m_is_dialog_showing = false;
		return;
	}
	if (m_is_dialog_showing) {
		m_dialog_label->setString(dialog.substr(0, m_n));
		m_n += 3;
	}
	else {
		m_dialog_label->setString(dialog);
		m_n = dialog.size()+1;
	}
}

bool DialogScene::initDialogFromSQL(std::string dialog_form_name) {

	std::string filename = CCFileUtils::sharedFileUtils()->fullPathForFilename("sql/sql.db");	//创建数据库的相对路径
	sqlite3* pdb;

	int ret = sqlite3_open(filename.c_str(), &pdb);	//打开数据库
	if (ret != SQLITE_OK) {	//如果打开数据库失败
		const char* errmsg = sqlite3_errmsg(pdb);
		CCLOG("sqlite open error: %s", errmsg);
		sqlite3_close(pdb);

		return false;
	}

	for (int i = 0; ; i++) {
		std::string sql = "select * from  " + dialog_form_name +" where ID=" + Value(i).asString();
		char** table; // 查询结果
		int r, c;     // 行数、列数
					  //开始查询
		sqlite3_get_table(pdb, sql.c_str(), &table, &r, &c, nullptr);

		if (table[1 * c + 1] == NULL)	break;

		std::string bg_picPath = table[1 * c + 1];
		std::string character_picPath = table[1 * c + 2];
		std::string name = table[1 * c + 3];
		std::string dialog = table[1 * c + 4];

		m_background_picPaths.push_back(bg_picPath);
		m_character_picPaths.push_back(character_picPath);
		m_names.push_back(name);
		m_dialogs.push_back(dialog);
	}
	auto text_cache = _director->getTextureCache();
	for (std::string character_textute : m_character_picPaths) {
		text_cache->addImage(character_textute);
	}
	for (std::string bg_texture : m_background_picPaths) {
		text_cache->addImage(bg_texture);
	}

	return true;
}