#include "PlayerWitchBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "Device.h"
#include "App.h"
#include "BulletBeam.h"
#include "BulletBubble.h"
#include "BulletLay.h"
#include "Weapon.h"

PlayerWitchBehavior::PlayerWitchBehavior( ) {
}

PlayerWitchBehavior::~PlayerWitchBehavior( ) {
}

void PlayerWitchBehavior::attack( ) {
	DevicePtr device = Device::getTask( );
	if ( device->getButton( ) == BUTTON_A && _befor_state != COMMON_STATE_ATTACK ) {
		_common_state = COMMON_STATE_ATTACK;
	}
	//UŒ‚’†
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_WITCH_ATTACK && !_animation->isEndAnimation( )  ) {
		if ( _animation->getAnimTime( ) == 20.0 ) {
			AppPtr app = App::getTask( );
			WeaponPtr weapon = app->getWeapon( );
			BulletPtr bullet;
			switch ( _attack_pattern ) {
				case 0:
					bullet = BulletBeamPtr( new BulletBeam( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
					break;
				case 1:
					bullet = BulletBubblePtr( new BulletBubble( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
					break;
				case 2:
					bullet = BulletLayPtr( new BulletLay( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
					break;
			}
			weapon->add( bullet );
<<<<<<< HEAD
			_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//UŒ‚ƒpƒ^[ƒ“‚Ì•ÏX
=======
>>>>>>> ecbe810430bbcd12329be2e619d0abbe806c138c
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
			switch ( _attack_pattern ) {
				case 0:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_ATTACK ) );
					break;
				case 1:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_ATTACK ) );
					break;
				case 2:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_ATTACK ) );
					break;
			}
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
