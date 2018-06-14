#pragma once

#ifndef _BASE_CARD_H_
#define _BASE_CARD_H_

#include"GameConfig.h"
#include"BaseEffect.h"
#include"Box2D\Box2D.h"
#include"CardID.h"
#include"Target.h"
#include<vector>

//只有这两样数值是会根据玩家改变的
//因此可以作为BaseCard的一部分，暴露至外部修改 
struct CardBaseProperty{
	int damage_number = 0;
	int armor_number = 0;
	int magic_number = 0;	//玩家智力
};
enum CardType {
	Attack_Card,//攻击牌
	Skill_Card,	//技能牌
	Magic_Card	//魔法牌
};

class BaseCard : public cocos2d::Node {
public:
	//ID、名字、说明、费用、卡牌背景
	static BaseCard * create(CardID cardID, std::string name, std::string info, std::string cost, std::string picPath, b2World* world);


	void effect(Target& target);
	void addEffect(BaseEffect* effect);
	void updateCardInfo();

	//void setPlayerNeed(int opt) { m_player_need = opt; }
	//void setEnemyNeed(int opt) { m_enemy_need = opt; }
	//void setCardLayerNeed(int opt) { m_card_layer_need = opt; }

	//int getPlayerNeed() { return m_player_need; }
	//int getEnemyNeed() { return m_enemy_need; }
	//int getCardLayerNeed() { return m_card_layer_need; }

	//void setIsNeedPlayer(bool flag) { m_isNeedPlayer = flag; }
	//void setIsNeedTarget(bool flag) { m_isNeedTarget = flag;}
	//bool getIsNeedPlayer() { return m_isNeedPlayer; }
	//bool getIsNeedTarget() { return m_isNeedTarget; }

	CardID getCardID() { return m_card_ID; }
	int getCardCost() { return Value(m_cardCost).asInt(); }

	Sprite* getCardSprite() { return m_cardSprite; }
	b2Body* getBody() { return m_body; }

	CardBaseProperty m_Property;
	CardBaseProperty m_pre_property;
	CardType m_card_type;

	TargetNeed m_target_need;

	void moveTo(Vec2 position, float time);
	void rotateTo(float rotation, float time);

	virtual Size getContentSize() { return m_cardSprite->getContentSize(); }
private:
	BaseCard();
	~BaseCard();

	virtual bool init(CardID cardID, std::string name, std::string info , std::string cost, std::string picPath, b2World* world);
	virtual void update(float dt);

	void updateCardProperty(Ref* pSender);

	//用于检测鼠标停放在卡牌贴图上时的函数
	virtual void onMouseMove(EventMouse* pEvent);
private:
	Sprite * m_cardSprite;	//卡牌精灵
	b2Body* m_body;

	CardID m_card_ID;

	//费用、名字、说明
	std::string m_cardCost;
	int m_pre_cardCost;
	std::string m_cardName;
	std::string m_cardInfo;

	Label* m_cardCost_label;
	Label* m_cardName_label;
	Label* m_cardInfo_label;

	//用以表示这张卡牌所有的Effect，当使用卡牌时，可以转为遍历所有的Effect，并调用effect函数
	Vector<BaseEffect*> m_effect_vector;
};
#endif // !_BASE_CARD_H_
