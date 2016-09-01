#include "PlayerMonkBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "Device.h"
#include "App.h"
#include "BulletImpact.h"
#include "Weapon.h"
#include "Network.h"

PlayerMonkBehavior::PlayerMonkBehavior( CameraConstPtr camera ) :
PlayerBehavior( camera ){
}


PlayerMonkBehavior::~PlayerMonkBehavior( ) {
}

void PlayerMonkBehavior::otherAction( ) {
	DevicePtr device = Device::getTask( );
	if ( device->getButton( ) == BUTTON_A && _befor_state != COMMON_STATE_ATTACK ) {
		_common_state = COMMON_STATE_ATTACK;
	}
	//UŒ‚’†
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_MONK_ATTACK && !_animation->isEndAnimation( ) ) {
		if ( _animation->getAnimTime( ) == 25.0 ) {
			AppPtr app = App::getTask( );
			WeaponPtr weapon = app->getWeapon( );
			BulletPtr bullet = BulletImpactPtr( new BulletImpact( _parent->getPos( ), _parent->getDir( ) ) );
			weapon->add( bullet );
		}
		_common_state = COMMON_STATE_ATTACK;
	}
}

void PlayerMonkBehavior::animationUpdate( ) {
	if ( _common_state == COMMON_STATE_DEAD && _animation->isEndAnimation( ) ) {
		_parent->dead( );
		return;
	}

	if ( _common_state == COMMON_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_MONK_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_WAIT ) );
		} else {
			if( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_MONK_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_WALK ) ); 
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_MONK_ATTACK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_ATTACK ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_MONK_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_DEAD ) );
		}
	}
}