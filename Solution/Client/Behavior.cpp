#include "Behavior.h"
#include "Animation.h"
#include <assert.h>

Behavior::Behavior( ) {
	_animation = AnimationPtr( new Animation( ) );
	_attack_pattern = 0;
}

Behavior::~Behavior( ) {
}

void Behavior::init( ) {
	_common_state = COMMON_STATE_WAIT;
	_befor_state = _common_state;
}

void Behavior::mainLoop( ) {
	update( );
	animationUpdate( );
	_animation->update( );
}

AnimationPtr Behavior::getAnimation( ) const {
	return _animation;
}

void Behavior::setParent( CharacterPtr parent ) {
	_parent = parent;
}