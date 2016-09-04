#include "PlayerHunterBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "Device.h"
#include "App.h"
#include "BulletMissile.h"
#include "Weapon.h"

PlayerHunterBehavior::PlayerHunterBehavior( ) {
}


PlayerHunterBehavior::~PlayerHunterBehavior( ) {
}

void PlayerHunterBehavior::otherAction( ) {
	DevicePtr device = Device::getTask( );
	if ( device->getButton( ) == BUTTON_A && _befor_state != COMMON_STATE_ATTACK ) {
		_common_state = COMMON_STATE_ATTACK;
	}
	//UŒ‚’†
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_ATTACK && !_animation->isEndAnimation( ) ) {
		if ( _animation->getAnimTime( ) == 20.0 ) {
			AppPtr app = App::getTask( );
			WeaponPtr weapon = app->getWeapon( );
			BulletPtr bullet = BulletMissilePtr( new BulletMissile( _parent->getPos( ), _parent->getDir( ) ) );
			weapon->add( bullet );
		}
		_common_state = COMMON_STATE_ATTACK;
	}
}

void PlayerHunterBehavior::animationUpdate( ) {
	if ( _common_state == COMMON_STATE_DEAD && _animation->isEndAnimation( ) ) {
		_parent->dead( );
		return;
	}

	if ( _common_state == COMMON_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_HUNTER_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_WAIT ) );
		} else {
			if( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_HUNTER_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_WALK ) ); 
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_HUNTER_ATTACK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_ATTACK ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_HUNTER_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_DEAD ) );
		}
	}
}