//  
//  Shake.cpp  
//  war  
//  

#include "CCShake.h"  

// not really useful, but I like clean default constructors  
CCShake::CCShake() : _strength_x(0), _strength_y(0), _initial_x(0), _initial_y(0)
{
}

CCShake* CCShake::create(float d, float strength)
{
	// call other construction method with twice the same strength  
	return create(d, strength, strength);
}

CCShake* CCShake::create(float duration, float strength_x, float strength_y)
{
	CCShake *p_action = new CCShake();
	p_action->initWithDuration(duration, strength_x, strength_y);
	p_action->autorelease();

	return p_action;
}

bool CCShake::initWithDuration(float duration, float strength_x, float strength_y)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		_strength_x = strength_x;
		_strength_y = strength_y;

		return true;
	}

	return false;
}

// Helper function. I included it here so that you can compile the whole file  
// it returns a random value between min and max included  
float fgRangeRand(float min, float max)
{
	float rnd = ((float)rand() / (float)RAND_MAX);
	return rnd * (max - min) + min;
}

void CCShake::update(float time)
{
	float randx = fgRangeRand(-_strength_x, _strength_x);
	float randy = fgRangeRand(-_strength_y, _strength_y);

	// move the target to a shaked position  
	_target->setPosition(Vec2(_initial_x + randx,
		_initial_y + randy));
}

CCShake* CCShake::clone(void) const
{
	auto a = new CCShake();
	a->initWithDuration(_duration, _strength_x, _strength_y);
	a->autorelease();
	return a;
}

CCShake* CCShake::reverse() const
{
	return CCShake::create(_duration, -_strength_x, -_strength_y);
}

void CCShake::startWithTarget(Node *target)
{
	CCActionInterval::startWithTarget(target);

	// save the initial position  
	_initial_x = target->getPosition().x;
	_initial_y = target->getPosition().y;
}

void CCShake::stop(void)
{
	// Action is done, reset clip position  
	_target->setPosition(Vec2(_initial_x, _initial_y));

	CCActionInterval::stop();
}