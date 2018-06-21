#include"CardSystem.h"
#include"EffectHeader.h"

BaseCard* CardSystem::createCardByID(CardID id) {
	//auto dict = Dictionary::createWithContentsOfFile("zh-cn.xml");

	std::string filename = CCFileUtils::sharedFileUtils()->fullPathForFilename("sql/sql.db");	//创建数据库的相对路径
	sqlite3* pdb;

	int ret = sqlite3_open(filename.c_str(), &pdb);	//打开数据库
	if (ret != SQLITE_OK) {	//如果打开数据库失败
		const char* errmsg = sqlite3_errmsg(pdb);
		CCLOG("sqlite open error: %s", errmsg);
		sqlite3_close(pdb);

		return NULL;
	}

	//寻找ID创建卡牌的基本信息
	std::string sql = "select * from card_zh_cn where ID=" + Value(id).asString();
	char** table; // 查询结果
	int r, c;     // 行数、列数
	//开始查询
	sqlite3_get_table(pdb, sql.c_str(), &table, &r, &c, nullptr);

	//创建卡牌基本信息
	std::string name = table[1 * c + 1];	//名字
	std::string info = table[1 * c + 2];	//信息
	std::string cost = table[1 * c + 3];	//费用
	std::string picPath = table[1 * c + 4];	//卡牌背景
	// 删除查询表
	sqlite3_free_table(table);

	BaseCard* card = BaseCard::create(id, name, info, cost, picPath, m_world);

	//根据ID添加效果
	switch (id) {
		case CardID::Strike:
			card->m_Property = card->m_pre_property = { -5 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 1 , 0 };
			card->m_card_type = CardType::Attack_Card;

			//添加对敌人伤害Effect
			card->addEffect(PropertyChangeEffect::create( TargetType::TO_ENEMY , Property::Health , &card->m_Property.damage_number /*&card->m_Property.damage_number*/));

			break;

		case CardID::Defend:
			card->m_Property = card->m_pre_property = { 0 , +5 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };
			card->m_card_type = CardType::Skill_Card;

			//添加对自己护甲Effect
			card->addEffect(PropertyChangeEffect::create( TargetType::TO_PLAYER , Property::Armor, &card->m_Property.armor_number /*&card->m_Property.armor_number*/));

			break;

		case CardID::Inner_Strength:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };
			card->m_card_type = CardType::Skill_Card;

			//添加力量改变Effect，该Effect为瞬间添加力量，不产生状态图标
			card->addEffect(PropertyChangeEffect::create( TargetType::TO_PLAYER ,Property::Power , new int(3)));
			//添加状态Effect，该状态用于回收力量，isCanEffect设为false则即每回合不会作用
			card->addEffect(StateEffect::create( TargetType::TO_PLAYER ,StateType::Property_Change , "state/inner_strength.png" , name , info , 1 , false , true , false , Property::Power , new int(3)));

			break;

		case CardID::Mortal_Strike:
			card->m_Property = card->m_pre_property = { -8 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 1 , 0 };
			card->m_card_type = CardType::Attack_Card;

			//对敌人造成8点伤害，如果小于等于30%伤害，则造成5倍伤害
			card->addEffect(ConditionRatioEffect::create(
				TargetType::TO_ENEMY, Property::Health, Condition_Way::Less_Equal, 0.3, TargetType::TO_ENEMY, Property::Health, &card->m_Property.damage_number , 5));
		
			break;

		case CardID::Armor_Breaking:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 1 , 0 };

			//条件Effect
			card->addEffect(
				ConditionEffect::create(
					TargetType::TO_ENEMY, Property::Armor, Condition_Way::Less_Equal, 10, TargetType::TO_ENEMY, Property::Armor, new int(-5), 2) );
			break;

		case CardID::Blessing_Of_Prince_Daughter: 
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };

			card->addEffect(StateEffect::create(TargetType::TO_PLAYER, StateType::Property_Change, "state/blessing_of_prince_daughter.png", name, info, 3, true, false, true, Property::Power, new int(1)));
			break;

		case CardID::Health_Potion:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };

			card->addEffect(StateEffect::create(TargetType::TO_PLAYER,StateType::Property_Change,  "state/health_potion.png", name, info, 6, true, false, true , Property::Health  ,new int(5)));
			break;

		case CardID::Preparation:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };

			card->addEffect(PropertyChangeEffect::create(TargetType::TO_PLAYER , Property::Cost , new int(1) ));
			break;

		case CardID::Split:
			card->m_Property = card->m_pre_property = { -4 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 1 , 0 };

			card->addEffect( StateEffect::create(TargetType::TO_ENEMY, StateType::Property_Change , "state/split.png", name, info, 3, true, false,false , Property::Health, &card->m_Property.damage_number ));

			break;

		case CardID::Cleave:
			card->m_Property = card->m_pre_property = { -7 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , -1 , 0 };

			card->addEffect(PropertyChangeEffect::create(TargetType::TO_ENEMY, Property::Health , &card->m_Property.damage_number ));

			break;

		case CardID::Pot_of_Avarice:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 0 , 1 };
	
			card->addEffect(DrawCardEffect::create(TargetType::TO_CARD_LAYER, 2, DrawFrom::From_Card_Library));
			break;

		case CardID::Burst_Limit:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };

			card->addEffect(PropertyChangeEffect::create(TargetType::TO_PLAYER, Property::Power, new int(0)));
			card->addEffect(StateEffect::create(TargetType::TO_PLAYER, StateType::Property_Change, "state/burst_limit.png", name, info, 1, false, true, false, Property::Power, new int(0)));
			break;

		case CardID::Tie:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 1 , 0 };

			card->addEffect(PropertyChangeEffect::create(TargetType::TO_ENEMY, Property::Power, new int(-6)));
			card->addEffect(StateEffect::create(TargetType::TO_ENEMY,StateType::Property_Change , "state/tie.png" , name , info , 1 ,false , true , false , Property::Power, new int(-6)));
			break;

		case CardID::Magic_Book:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };

			card->addEffect(ConditionEffect::create(TargetType::TO_PLAYER, Property::Magic, Condition_Way::Greater_Equal, 10, TargetType::TO_PLAYER, Property::Magic, new int(2), 2 ));
			break;

		case CardID::Magic_Missile:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , -1 , 0 };

			//3次，对随机目标造成[智力]点伤害
			card->addEffect(DamageEffect::create(TargetType::TO_ENEMY, &card->m_Property.magic_number, 3, true));
			//card->addEffect(RandomTargetDamageEffect::create(TargetType::TO_ENEMY, &card->m_Property.magic_number, 3));
			break;

		case CardID::Enchanted_Weapon:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 0 };
			card->m_card_type = CardType::Magic_Card;	//魔法卡牌

			card->addEffect(PropertyChangeEffect::create(TargetType::TO_PLAYER, Property::Power, new int(5)));
			break;

		case CardID::Arcane_Breath:
			card->m_Property = card->m_pre_property = { 0 , 0 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 0 , 1 , 0 };
			card->m_card_type = CardType::Magic_Card;	//魔法卡牌

			//造成5倍智力的伤害，因为敌人血量一定大于0，所以条件永远成立
			card->addEffect(ConditionEffect::create(TargetType::TO_ENEMY, Property::Health, Condition_Way::Greater_Equal, 0, TargetType::TO_ENEMY, Property::Health, &card->m_Property.magic_number, -6));
			break;

		case CardID::Backflip:
			card->m_Property = card->m_pre_property = { 0 , +3 , 0 };
			card->updateCardInfo();
			card->m_target_need = { 1 , 0 , 1 };

			card->addEffect(DrawCardEffect::create(TargetType::TO_CARD_LAYER, 4, DrawFrom::From_Card_Library));
			card->addEffect(PropertyChangeEffect::create(TargetType::TO_PLAYER, Property::Armor, &card->m_Property.armor_number));
			break;
	}

	//关闭数据库
	sqlite3_close(pdb);
	return card;
}

b2World* CardSystem::m_world = new b2World(b2Vec2(0.0f, 0.0f));