#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"BaseCharacter.h"

class Player :public BaseCharacter {
public:
	//图片路径、最大HP、护甲、力量、敏捷、智力、最高费用
	static Player* create(std::string picPath, int max_hp, int armor, int power, int agility, int magic , int max_cost );

	//改变智力
	void changeMagic(int magic);
	//改变费用
	void changeCost(int cost);
	//重置费用
	void resetCost() { m_cost = m_max_cost; }
	//改变最大费用
	void changeMaxCost(int max_cost);

	int getMagic() { return m_Magic; }
	int getCost() { return m_cost; }
	int getMaxCost() { return m_max_cost; }
	//是否有智力值
	bool isHaveMagic() { return m_isHaveMagic; }

	void effect_when_round_end();
private:
	Player();
	~Player();

	//图片路径、最大HP、护甲、力量、敏捷、智力
	bool init(std::string picPath, int max_hp, int armor, int power, int agility, int magic , int max_cost );
private:
	int m_Magic;	//智力值
	bool m_isHaveMagic;	//是否有智力值

	Label* m_magic_label;	//智力Label

	int m_max_cost;
	int m_cost;
};
#endif // !_PLAYER_H_