#include "PlayerKnightBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "Device.h"
#include "App.h"
#include "BulletSword.h"
#include "BulletSlash.h"
#include "BulletStab.h"
#include "Weapon.h"

PlayerKnightBehavior::PlayerKnightBehavior( ) {
}

PlayerKnightBehavior::~PlayerKnightBehavior( ) {
}

void PlayerKnightBehavior::attack( ) {
	DevicePtr device = Device::getTask( );
	//UŒ‚‚É“ü‚éuŠÔ
	if ( device->getButton( ) == BUTTON_A && _before_state != PLAYER_STATE_ATTACK ) {
		AppPtr app = App::getTask( );
		WeaponPtr weapon = app->getWeapon( );
		BulletPtr bullet;
		switch ( _attack_pattern ) {
			case 0:
				bullet = BulletSlashPtr( new BulletSlash( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ).x, _parent->getDir( ).y ) );
				break;
			case 1:
				bullet = BulletSwordPtr( new BulletSword( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ).x, _parent->getDir( ).y ) );
				break;
			case 2:
				bullet = BulletStabPtr( new BulletStab( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ).x, _parent->getDir( ).y ) );
				break;
		}
		weapon->add( bullet );
		_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//UŒ‚ƒpƒ^[ƒ“‚Ì•ÏX
		_player_state = PLAYER_STATE_ATTACK;
	}
	//UŒ‚’†
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_ATTACK && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_ATTACK;
	}
}

void PlayerKnightBehavior::animationUpdate( ) {
	if ( _player_state == PLAYER_STATE_DEAD && _animation->isEndAnimation( ) ) {
		_parent->dead( );
		return;
	}

	if ( _player_state == PLAYER_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_WAIT ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_WALK ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_ATTACK ) {
			switch ( _attack_pattern ) {
				case 0:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_ATTACK ) );
					break;
				case 1:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_ATTACK ) );
					break;
				case 2:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_ATTACK ) );
					break;
			}
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_DEAD ) );
		}
	}
}