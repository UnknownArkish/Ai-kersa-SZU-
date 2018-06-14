#pragma once

#ifndef _CARD_ID_H_
#define _CARD_ID_H_

//注释为卡牌名字，ID（对应数据库），说明
enum CardID {
	Strike = 0,	//打击0
	Defend,	//防御1
	Inner_Strength,	//内在潜力2:回合结束后增加2点力量
	Mortal_Strike,	//致死打击3
	Armor_Breaking,	//破甲4
	Blessing_Of_Prince_Daughter,	//王女的祝福5
	Health_Potion,	//治疗药水6
	Preparation,	//克敌先机7
	Split,	//割裂8
	Cleave,	//横劈9
	Pot_of_Avarice,	//贪欲之壶10
	Burst_Limit,	//突破极限11
	Tie,	//束缚12
	Magic_Book,	//魔法书13
	Magic_Missile,	//魔法飞弹14
	Enchanted_Weapon,	//法力武器
	Arcane_Breath,	//奥术吐息
	Backflip	//后空翻
};
//后续添加ID就是各种各样的卡牌

#endif // !_CARD_ID_H_