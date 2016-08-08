#include "Behavior.h"
#include "Animation.h"
#include <assert.h>

Behavior::Behavior( ) {
}

Behavior::~Behavior( ) {
}

void Behavior::update( ) {
	if( !_parent ) {
		assert( "NotParent" );
	}
	moveUpdate( );
	animationUpdate( );
}

void Behavior::animationUpdate( ) {
	_animetion->update( );
}

AnimationPtr Behavior::getAnimation( ) const {
	return _animetion;
}

void Behavior::setParent( CharacterPtr parent ) {
	_parent = parent;
}