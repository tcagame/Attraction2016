#include "PlayerMonkBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "Device.h"
#include "App.h"
#include "BulletJab.h"
#include "BulletImpact.h"
#include "BulletUpper.h"
#include "Weapon.h"
#include "Network.h"

PlayerMonkBehavior::PlayerMonkBehavior( ) {
}


PlayerMonkBehavior::~PlayerMonkBehavior( ) {
}

void PlayerMonkBehavior::attack( ) {
	DevicePtr device = Device::getTask( );
	if ( device->getButton( ) == BUTTON_A && _befor_state != COMMON_STATE_ATTACK ) {
		_common_state = COMMON_STATE_ATTACK;
	}
	//UŒ‚’†
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_MONK_ATTACK && !_animation->isEndAnimation( ) ) {
		if ( _animation->getAnimTime( ) == 30.0 ) {
			AppPtr app = App::getTask( );
			WeaponPtr weapon = app->getWeapon( );
			BulletPtr bullet;
			switch ( _attack_pattern ) {
			case 0:
				bullet = BulletJabPtr( new BulletJab( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
				break;																									 
			case 1:																										 
				bullet = BulletImpactPtr( new BulletImpact( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
				break;																									 
			case 2:																										 
				bullet = BulletUpperPtr( new BulletUpper( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
				break;
			}
			weapon->add( bullet );
			_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//UŒ‚ƒpƒ^[ƒ“‚Ì•ÏX
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
			switch ( _attack_pattern ) {
				case 0:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_ATTACK, 1.5 ) );
					break;
				case 1:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_ATTACK, 1.5 ) );
					break;
				case 2:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_ATTACK, 1.5 ) );
					break;
			}
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