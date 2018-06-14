#include"BaseEffect.h"

bool BaseEffect::init(TargetType type) {
	if (!Node::init()) {
		return false;
	}
	m_type = type;
	return true;
}