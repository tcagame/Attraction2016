#include "Behavior.h"
#include "Animation.h"
#include <assert.h>

Behavior::Behavior( ) {
	reset( );
}

Behavior::~Behavior( ) {
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

void Behavior::reset( ) {
	_animation = AnimationPtr( new Animation );
}