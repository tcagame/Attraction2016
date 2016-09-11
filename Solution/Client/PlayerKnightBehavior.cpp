#include "PlayerKnightBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "Device.h"
#include "App.h"
#include "BulletSword.h"
#include "BulletSlash.h"
#include "BulletStab.h"
#include "BulletExcalibur.h"
#include "Weapon.h"
#include "Player.h"

PlayerKnightBehavior::PlayerKnightBehavior( ) {
}

PlayerKnightBehavior::~PlayerKnightBehavior( ) {
}

void PlayerKnightBehavior::attack( ) {
	DevicePtr device = Device::getTask( );
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	BulletPtr bullet;
	
	//ïKéEãZÇÃç\Ç¶
	PlayerPtr player = std::dynamic_pointer_cast< Player >( _parent );
	//ó≠ÇﬂÉÇÅ[ÉVÉáÉì
	if ( device->getButton( ) == BUTTON_D && ( _before_state == PLAYER_STATE_WAIT || _before_state == PLAYER_STATE_WALK || _before_state == PLAYER_STATE_ATTACK ) /*&& player->getSP( ) == 100*/ ) {
		_player_state = PLAYER_STATE_STORE;
	}
	//ó≠Çﬂéùë±
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_STORE && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_STORE;
	}
	//ïKéEãZÇÇ§Ç¬
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_STORE && _animation->isEndAnimation( ) ) {
		bullet = BulletPtr( new BulletExcalibur( _parent->getPos( ), _parent->getDir( ) ) );
		weapon->add( bullet );
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	//ïKéEãZèIóπÇ‹Ç≈ïKéEãZÉÇÅ[ÉVÉáÉì
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_DEATHBLOW && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_DEATHBLOW;
	}

	if ( !isDeathblow( ) ) {
		//çUåÇÇ…ì¸ÇÈèuä‘
		if ( device->getButton( ) == BUTTON_A && _before_state != PLAYER_STATE_ATTACK ) {
			_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//çUåÇÉpÉ^Å[ÉìÇÃïœçX
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
			_player_state = PLAYER_STATE_ATTACK;
		}
		//çUåÇíÜ
		if ( ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_ATTACK_SLASH ||
			  _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_ATTACK_SWORD ||
			  _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_ATTACK_STAB ) && !_animation->isEndAnimation( ) ) {
			_player_state = PLAYER_STATE_ATTACK;
		}
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
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_ATTACK_SLASH &&
			 _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_ATTACK_STAB &&
			 _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_ATTACK_SWORD ) {
			switch ( _attack_pattern ) {
				case 0:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_ATTACK_SLASH ) );
					break;
				case 1:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_ATTACK_SWORD ) );
					break;
				case 2:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_ATTACK_STAB ) );
					break;
			}
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_STORE ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_STORE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_STORE ) );
		}
	}
	if ( _player_state == PLAYER_STATE_DEATHBLOW ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_DEATHBLOW ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_DEATHBLOW ) );
		}
	}
	if ( _player_state == PLAYER_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_DEAD ) );
		}
	}
}