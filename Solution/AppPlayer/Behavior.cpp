#include "Behavior.h"
#include "Animation.h"
#include <assert.h>

Behavior::Behavior( ) {
	_common_state = COMMON_STATE_WAIT;
	_befor_state = _common_state;
}

Behavior::~Behavior( ) {
}

AnimationPtr Behavior::getAnimation( ) const {
	return _animation;
}

void Behavior::setParent( CharacterPtr parent ) {
	_parent = parent;
}