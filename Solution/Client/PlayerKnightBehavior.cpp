#include "PlayerKnightBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "Device.h"
#include "App.h"
#include "BulletSword.h"
#include "Weapon.h"

#include "Drawer.h"

PlayerKnightBehavior::PlayerKnightBehavior( ) {
}

PlayerKnightBehavior::~PlayerKnightBehavior( ) {
}

void PlayerKnightBehavior::otherAction( ) {
	DevicePtr device = Device::getTask( );
	//UŒ‚‚É“ü‚éuŠÔ
	if ( device->getButton( ) == BUTTON_A && _befor_state != COMMON_STATE_ATTACK ) {
		AppPtr app = App::getTask( );
		WeaponPtr weapon = app->getWeapon( );
		BulletPtr bullet = BulletSwordPtr( new BulletSword( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ).x, _parent->getDir( ).y ) );
		weapon->add( bullet );
		_common_state = COMMON_STATE_ATTACK;

		DrawerPtr drawer = Drawer::getTask( );
		Drawer::Effect effect;
		effect.pos = _parent->getPos( ) + Vector( 0, 0, 5 );
		effect.dir = _parent->getDir( );
		effect.res = 0;
		drawer->setEffect( effect );
	}
	//UŒ‚’†
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_ATTACK && !_animation->isEndAnimation( ) ) {
		_common_state = COMMON_STATE_ATTACK;
	}
}

void PlayerKnightBehavior::animationUpdate( ) {
	if ( _common_state == COMMON_STATE_DEAD && _animation->isEndAnimation( ) ) {
		_parent->dead( );
		return;
	}

	if ( _common_state == COMMON_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_WAIT ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_WALK ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_ATTACK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_ATTACK ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_DEAD ) );
		}
	}
}