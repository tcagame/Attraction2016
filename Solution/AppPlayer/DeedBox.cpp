#include "DeedBox.h"
#include "Animation.h"


DeedBox::DeedBox( Vector pos ) {
	_pos = pos;
	_dir = Vector( 0, 1, 0 );
	_phase = PHASE_CLOSE;
	_animation = AnimationPtr( new Animation( Animation::MOTION_DEEDBOX ) );
}


DeedBox::~DeedBox( ) {

}

void DeedBox::update( ) {

	if ( _phase == PHASE_UNLOCK ) {
		_animation->update( );
	}
	if ( _phase == PHASE_UNLOCK && _animation->isEndAnimation( ) ) {
		_phase = PHASE_OPEN;
	}
}

Vector DeedBox::getPos( ) const {
	return _pos;
}

Vector DeedBox::getDir( ) const {
	return _dir;
}

AnimationPtr DeedBox::getAnimation( ) {
	return _animation;
}

void DeedBox::pickup( ) {
	if ( _phase == PHASE_CLOSE ) {
		_phase = PHASE_UNLOCK;
		_animation = AnimationPtr( new Animation( Animation::MOTION_DEEDBOX ) );
	}
}