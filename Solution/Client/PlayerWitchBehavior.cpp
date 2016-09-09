#include "PlayerWitchBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "Device.h"
#include "App.h"
#include "BulletBeam.h"
#include "BulletBubble.h"
#include "BulletLay.h"
#include "BulletSplash.h"
#include "Weapon.h"
#include "Player.h"

PlayerWitchBehavior::PlayerWitchBehavior( ) {
}

PlayerWitchBehavior::~PlayerWitchBehavior( ) {
}

void PlayerWitchBehavior::attack( ) {
	DevicePtr device = Device::getTask( );
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	BulletPtr bullet;
	if ( isDeathblow( ) ) {
		if ( device->getButton( ) == BUTTON_A && _before_state != PLAYER_STATE_ATTACK ) {
			_player_state = PLAYER_STATE_ATTACK;
		}
		//攻撃中
		if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_WITCH_ATTACK && !_animation->isEndAnimation( )  ) {
			if ( _animation->getAnimTime( ) == 20.0 ) {
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
				_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//攻撃パターンの変更
			}
			_player_state = PLAYER_STATE_ATTACK;
		}
	}
	//必殺技の構え
	PlayerPtr player = std::dynamic_pointer_cast< Player >( _parent );
	//溜めモーション
	if ( device->getButton( ) == BUTTON_D && ( _before_state == PLAYER_STATE_WAIT || _before_state == PLAYER_STATE_WALK || _before_state == PLAYER_STATE_ATTACK ) /*&& player->getSP( ) == 100*/ ) {
		_player_state = PLAYER_STATE_STORE;
	}
	//溜め持続
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_STORE && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_STORE;
	}
	//必殺技をうつ
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_STORE && _animation->isEndAnimation( ) ) {
		bullet = BulletPtr( new BulletSplash( _parent->getPos( ), _parent->getDir( ) ) );
		weapon->add( bullet );
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	//必殺技終了まで必殺技モーション
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_DEATHBLOW && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
}


void PlayerWitchBehavior::animationUpdate( ) {
	if ( _player_state == PLAYER_STATE_DEAD && _animation->isEndAnimation( ) ) {
		_parent->dead( );
		return;
	}

	if ( _player_state == PLAYER_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_WAIT ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_WALK ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_ATTACK ) {
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
	if ( _player_state == PLAYER_STATE_STORE ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_STORE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_STORE ) );
		}
	}
	if ( _player_state == PLAYER_STATE_DEATHBLOW ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_DEATHBLOW ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_DEATHBLOW ) );
		}
	}
	if ( _player_state == PLAYER_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_DEAD ) );
		}
	}
}
