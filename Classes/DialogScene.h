#pragma once

#ifndef _DIALOG_SCENE_H_
#define _DIALOG_SCENE_H_

#include"GameConfig.h"

#define TAG_DIALOG_COLOR_LAYER 1000
#define TAG_NAME_COLOR_LAYER 1001

class DialogScene :public Layer {
//public:
//	static Scene* createScene( );	//用以测试使用
//	static Scene* createScene(std::string dialog_form_name );	//dialog表单名

protected:
	static DialogScene* create(std::string dialog_form_name );
	virtual bool init( std::string dialog_form_name );

private:

	//从数据库中初始化
	bool initDialogFromSQL( std::string dialog_form_name );
	//更新对话框（使逐渐显示）
	void toUpdateDialog();
	//结束对话场景
	virtual void endDialogScene(Ref* ref) = 0;

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

protected:
	LayerColor * m_mask_layer;

private:
	Size m_visibleSize;

	std::vector<std::string> m_background_picPaths;
	std::vector<std::string> m_character_picPaths;
	std::vector<std::string> m_names;
	std::vector<std::string> m_dialogs;

	std::string m_pre_background_picPath;
	std::string m_pre_character_picPath;
	std::string m_pre_name;

	int m_counter = 0;
	int m_n;	//辅助逐渐显示dialog

	Sprite* m_background_sprite;
	Sprite* m_character_sprite;
	Label* m_name_label;
	Label* m_dialog_label;

	bool m_is_dialog_showing;
};


#endif // !_DIALOG_SCENE_H_
