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
#include "Effect.h"

PlayerWitchBehavior::PlayerWitchBehavior( ) :
PlayerBehavior( PLAYER_WITCH ) {
}

PlayerWitchBehavior::~PlayerWitchBehavior( ) {
}

void PlayerWitchBehavior::attack( ) {
	DevicePtr device = Device::getTask( );
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	BulletPtr bullet;
	//ïKéEãZÇÃç\Ç¶
	PlayerPtr player = std::dynamic_pointer_cast< Player >( _parent );
	//ó≠ÇﬂÉÇÅ[ÉVÉáÉì
	if ( device->getButton( ) == BUTTON_D && ( _before_state == PLAYER_STATE_WAIT || _before_state == PLAYER_STATE_WALK || _before_state == PLAYER_STATE_ATTACK ) && player->getSP( ) == 100 ) {
		Effect effect;
		int id = effect.setEffect( Effect::EFFECT_PLAYER_HUNTER_STORE );
		effect.drawEffect( id, Vector( 1, 1, 1 ), _parent->getPos( ) + Vector( 0, 0, 0.5 ),_parent->getDir( ) );
		_player_state = PLAYER_STATE_STORE;
	}
	//ó≠Çﬂéùë±
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_WITCH_STORE && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_STORE;
	}
	//ïKéEãZÇÇ§Ç¬
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_WITCH_STORE && _animation->isEndAnimation( ) ) {
		bullet = BulletPtr( new BulletSplash( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
		player->resetSP( );
		weapon->add( bullet );
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	//ïKéEãZèIóπÇ‹Ç≈ïKéEãZÉÇÅ[ÉVÉáÉì
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_WITCH_DEATHBLOW && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_DEATHBLOW;
	}

	if ( !isDeathblow( ) ) {
		if ( device->getButton( ) == BUTTON_A && _before_state != PLAYER_STATE_ATTACK ) {
			_player_state = PLAYER_STATE_ATTACK;
		}
		//çUåÇíÜ
		if ( ( _animation->getMotion( ) == Animation::MOTION_PLAYER_WITCH_ATTACK_BEAM || 
			 _animation->getMotion( ) == Animation::MOTION_PLAYER_WITCH_ATTACK_BUBBLE || 
			 _animation->getMotion( ) == Animation::MOTION_PLAYER_WITCH_ATTACK_LAY ) 
										&& !_animation->isEndAnimation( )  ) {
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
				_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//çUåÇÉpÉ^Å[ÉìÇÃïœçX
			}
			_player_state = PLAYER_STATE_ATTACK;
		}
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
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_ATTACK_BEAM && 
			_animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_ATTACK_BUBBLE && 
			_animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_ATTACK_LAY  ) {
			switch ( _attack_pattern ) {
				case 0:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_ATTACK_BEAM ) );
					break;
				case 1:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_ATTACK_BUBBLE ) );
					break;
				case 2:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_ATTACK_LAY ) );
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
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_STORE, 0.25 ) );
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
