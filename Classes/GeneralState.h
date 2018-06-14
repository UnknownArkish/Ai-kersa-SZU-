#pragma once
#ifndef _GENERAL_STATE_H_
#define _GENERAL_STATE_H_

#include"BaseEffect.h"

//用以生成一般的State，即仅仅是一个State，具体用到时才能产生作用
class GeneralState : public BaseState {
public:
	//状态类型ID、状态精灵路径、状态名字、状态信息、持续回合数、是否可以叠加
	static GeneralState* create(
		StateType type, std::string picPath, std::string name, std::string info, int rounds, bool isCanOverlay);

	virtual void effect();
	virtual void effect_when_end();
private:
	bool init( StateType type , std::string picPath, std::string name, std::string info, int rounds , bool isCanOverlay);
private:
};

#endif // !_GENERAL_STATE_H_