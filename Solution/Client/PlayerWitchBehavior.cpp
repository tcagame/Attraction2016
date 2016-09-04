#include "PlayerWitchBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "Device.h"
#include "App.h"
#include "BulletLay.h"
#include "Weapon.h"

PlayerWitchBehavior::PlayerWitchBehavior( ) {
}

PlayerWitchBehavior::~PlayerWitchBehavior( ) {
}

void PlayerWitchBehavior::otherAction( ) {
	DevicePtr device = Device::getTask( );
	if ( device->getButton( ) == BUTTON_A && _befor_state != COMMON_STATE_ATTACK ) {
		_common_state = COMMON_STATE_ATTACK;
	}
	//UŒ‚’†
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_WITCH_ATTACK && !_animation->isEndAnimation( )  ) {
		if ( _animation->getAnimTime( ) == 20.0 ) {
			AppPtr app = App::getTask( );
			WeaponPtr weapon = app->getWeapon( );
			BulletPtr bullet = BulletLayPtr( new BulletLay( _parent->getPos( ), _parent->getDir( ) ) );
			weapon->add( bullet );
		}
		_common_state = COMMON_STATE_ATTACK;
	}
}


void PlayerWitchBehavior::animationUpdate( ) {
	if ( _common_state == COMMON_STATE_DEAD && _animation->isEndAnimation( ) ) {
		_parent->dead( );
		return;
	}

	if ( _common_state == COMMON_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_WAIT ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_WALK ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_ATTACK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_ATTACK ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_DEAD ) );
		}
	}
}
