#include "PlayerBehavior.h"
#include "Character.h"
#include "Camera.h"
#include "Animation.h"
#include "mathmatics.h"
#include "App.h"
#include "GroundModel.h"

PlayerBehavior::PlayerBehavior( CameraConstPtr camera ) {
	_camera = camera;
}

PlayerBehavior::~PlayerBehavior( ) {
}

void PlayerBehavior::update( ) {
	_common_state = COMMON_STATE_WAIT;

	Vector move_vec = _camera->getConvertDeviceVec( );
	Character::STATUS status = _parent->getStatus( );
	if ( _befor_state != COMMON_STATE_ATTACK && _befor_state != COMMON_STATE_DEAD ) {
		if ( move_vec.getLength( ) > 0.0 ) {
			AppPtr app = App::getTask( );
			GroundModelPtr ground_model = app->getGroundModel( );
			Vector move_pos = _parent->getPos( ) + move_vec;
			if( ground_model->isCollisionGround( move_pos ) ) {
				_parent->move( move_vec * status.speed );
			}
			_common_state = COMMON_STATE_WALK;
		}
	}
	otherAction( );
	if ( _parent->getStatus( ).hp <= 0 ) {
		_common_state = COMMON_STATE_DEAD;
	}
	_befor_state = _common_state;
}	