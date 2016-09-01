#include "LiveCamera.h"

const Vector START_CAMERA_POS = Vector( 30, 30, 7 );
const Vector START_TARGET_POS = Vector( 0, 0, 0 );

LiveCamera::LiveCamera( ) :
_pos( START_CAMERA_POS ), 
_target( START_TARGET_POS ) {
}

LiveCamera::~LiveCamera( ) {
}

Vector LiveCamera::getPos( ) const {
	return _pos;
}

Vector LiveCamera::getTarget( ) const {
	return _target;
}

void LiveCamera::setTarget( Vector target ) {
	_target = target;
}

void LiveCamera::update( ) {
	Vector vec = _pos - _target;
	_pos = _target + vec;
}