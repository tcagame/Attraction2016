#include "PlayerKnightBehavior.h"
#include "Animation.h"
#include "Device.h"

PlayerKnightBehavior::PlayerKnightBehavior( CameraConstPtr camera ) :
PlayerBehavior( camera ) {
	_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WAIT ) );
}

PlayerKnightBehavior::~PlayerKnightBehavior( ) {
}

void PlayerKnightBehavior::otherAction( ) {
	DevicePtr device = Device::getTask( );
	if ( device->isHoldButton( Device::BUTTON_LIST_1 ) && _common_state != COMMON_STATE_ATTACK ) {
		_common_state = COMMON_STATE_ATTACK;
	}
	if ( _befor_state == COMMON_STATE_ATTACK && _animation->isEndAnimation( ) ) {
		_common_state = COMMON_STATE_ATTACK;
	}
}

void PlayerKnightBehavior::animationUpdate( ) {
	if ( !_animation->isEndAnimation( ) ) {
		return;
	}
	if ( _common_state == COMMON_STATE_WAIT ) {
		_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WAIT ) );
	}
	if ( _common_state == COMMON_STATE_WALK ) {
		_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WALK ) );
	}
	if ( _common_state == COMMON_STATE_ATTACK ) {
		_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_ATTACK ) );
	}
	if ( _common_state == COMMON_STATE_DEAD ) {
		_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_DEAD ) );
	}
}