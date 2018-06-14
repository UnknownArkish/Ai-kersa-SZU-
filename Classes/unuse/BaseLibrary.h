#pragma once
#ifndef _BASE_LIBRARY_H_
#define _BASE_LIBRARY_H_

#include"GameConfig.h"
#include"BaseCard.h"
#include"CardSystem.h"
#include<vector>

class BaseLibrary :public Node{
public:
	static BaseLibrary* create(std::string picPath);
	static BaseLibrary* create(std::string picPath, std::vector<CardID>& cardID);

	//添加卡牌
	void addCard(BaseCard*& card);
	void addCard(CardID cardID);
	void addCard(int cardID);

	//抽取卡牌（不检测牌库大小是否允许）
	BaseCard*& drawCard();

	int getLibrarySize() { return m_library.size(); }	//获得牌库大小
private:
	virtual bool init(std::string picPath, std::vector<CardID>& cardID);
	virtual bool init(std::string picPath);

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);	//用以创建一个查看所有卡牌的Layer

private:
	Vector<BaseCard*> m_library;

	Sprite * m_library_sprite;

};

#endif // !_BASE_LIBRARY_H_
