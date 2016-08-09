#include "PlayerBehavior.h"
#include "Character.h"
#include "Camera.h"
#include "Animation.h"
#include "mathmatics.h"

PlayerBehavior::PlayerBehavior( CameraConstPtr camera ) {
	_camera = camera;
}

PlayerBehavior::~PlayerBehavior( ) {
}

void PlayerBehavior::update( ) {
	_common_state = COMMON_STATE_WAIT;
	
	Vector move_vec = _camera->getConvertDeviceVec( );
	Character::STATUS status = _parent->getStatus( );
	if ( move_vec.getLength( ) > 0 ) {
		_parent->move( move_vec * status.speed );
		_common_state = COMMON_STATE_WALK;
	}
	otherAction( );
	if ( _parent->getStatus( ).hp <= 0 ) {
		_common_state = COMMON_STATE_DEAD;
	}

	animationUpdate( );

	_befor_state = _common_state;
	_animation->update( );
}	