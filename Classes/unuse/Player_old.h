#pragma once

#ifndef _Player__OLD_H_
#define _Player__OLD_H_

#include"GameConfig.h"

class Player_ :public Node {
public:
	//贴图路径、最大生命值
	static Player_* create(std::string picPath, int max_hp , int armor , int power , int agility , int magic );

	//伤害、治疗
	void hurt(int damage);
	void heal(int health);

	//改变最大生命值
	void changeMaxHP(int max_hp);
	//改变护甲值
	void changeArmor(int armor);

	//改变力量、敏捷、智力值
	void changePower(int power);
	void changeAgility(int agility);
	void changeMagic(int magic);

	int getHP() { return m_hp; }	//获得生命值
	int getMaxHP() { return m_max_hp; }	//获得最大生命值
	int getArmor() { return m_Armor; }	//护甲值
	int getPower() { return m_Power; }	//力量值
	int getAgility() { return m_Agility; }	//敏捷值
	int getMagic() { return m_Magic; }	//智力值

	bool isHaveArmor() { return m_isHaveArmor; }	//是否有护甲值
	bool isHavePower() { return m_isHavePower; }
	bool isHaveAgility() { return m_isHaveAgility; }
	bool isHaveMagic() { return m_isHaveMagic; }

private:
	Player_();
	~Player_();

	virtual bool init(std::string picPath, int max_hp, int armor, int power, int agility, int magic);

	//更新HP_Label
	void updateHPLabel();

private:
	int m_hp;	//生命值
	int m_max_hp;	//最大生命值

	int m_Armor;	//当前护甲
	int m_Power;	//当前力量
	int m_Agility;	//当前敏捷
	int m_Magic;	//当前智力

	bool m_isDead;

	bool m_isHaveArmor;	//是否有护甲
	bool m_isHavePower;	//是否有力量
	bool m_isHaveAgility;	//敏捷
	bool m_isHaveMagic;	//智力

	Sprite* m_Player__sprite;	//玩家贴图
	Label* m_hp_label;	//生命值Label

	//先暂时用Label表示护甲、力量、敏捷和智力，后面可能改为图标，并放在一个Layer当中
	Label* m_armor_label;
	Label* m_power_label;
	Label* m_agility_label;
	Label* m_magic_label;
};

#endif // ! _Player__H_
