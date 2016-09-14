#include "PlayerWitchBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "App.h"
#include "BulletBeam.h"
#include "BulletBubble.h"
#include "BulletLay.h"
#include "BulletSplash.h"
#include "Weapon.h"
#include "Player.h"
#include "Sound.h"
#include "Effect.h"
#include "Client.h"
#include "Adventure.h"

const int WAIT_MAX = 600;

PlayerWitchBehavior::PlayerWitchBehavior( unsigned char player_id ) :
PlayerBehavior( PLAYER_WITCH, player_id ) {
}

PlayerWitchBehavior::~PlayerWitchBehavior( ) {
}

void PlayerWitchBehavior::attack( const CONTROLL& controll ) {
	SoundPtr sound = Sound::getTask( );
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	BulletPtr bullet;
	//ïKéEãZÇÃç\Ç¶
	PlayerPtr player = std::dynamic_pointer_cast< Player >( _parent );
	//ó≠ÇﬂÉÇÅ[ÉVÉáÉì
	
	if ( _before_state == PLAYER_STATE_WAIT ||
		 _before_state == PLAYER_STATE_WALK ||
		 _before_state == PLAYER_STATE_ATTACK ) {

		bool enabled = false;
		if ( controll.action == CONTROLL::DEATHBLOW && player->isFulledSP( ) ) {
			enabled = true;
		}
		if ( controll.action == CONTROLL::MUSTDEATHBLOW ) {
			enabled = true;
		}
		if ( enabled ) {
			Effect effect;
			int id = effect.setEffect( Effect::EFFECT_PLAYER_HUNTER_STORE );
			effect.drawEffect( id, Vector( 1, 1, 1 ), _parent->getPos( ) + Vector( 0, 0, 0.5 ),_parent->getDir( ) );
			_player_state = PLAYER_STATE_STORE;
			sound->playSE( Sound::SE_PLAYER_STORE );
			AdventurePtr adventure = app->getAdventure( );
			adventure->set( Adventure::TYPE_WITCH_STORE );
			if ( _controll ) {
				ClientPtr client = Client::getTask( );
				SERVERDATA data;
				data.command = COMMAND_STATUS_ACTION;
				data.value[ 0 ] = _player_id;
				data.value[ 1 ] = ACTION_DEATHBLOW;
				client->send( data );	
			}
		}
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
		sound->playSE( Sound::SE_WITCH_DEATHBLOW );
		AdventurePtr adventure = app->getAdventure( );
		adventure->set( Adventure::TYPE_WITCH_DEATHBLOW );
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	//ïKéEãZèIóπÇ‹Ç≈ïKéEãZÉÇÅ[ÉVÉáÉì
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_WITCH_DEATHBLOW && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_DEATHBLOW;
	}

	if ( !isDeathblow( ) ) {
		if ( controll.action == CONTROLL::ATTACK && _before_state != PLAYER_STATE_ATTACK ) {
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
						sound->playSE( Sound::SE_WITCH_ATTACK_1 );
						bullet = BulletBeamPtr( new BulletBeam( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
						break;
					case 1:
						sound->playSE( Sound::SE_WITCH_ATTACK_2 );
						bullet = BulletBubblePtr( new BulletBubble( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
						break;
					case 2:
						sound->playSE( Sound::SE_WITCH_ATTACK_3 );
						bullet = BulletLayPtr( new BulletLay( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
						break;
				}
				weapon->add( bullet );	
				_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//çUåÇÉpÉ^Å[ÉìÇÃïœçX
			}
			_player_state = PLAYER_STATE_ATTACK;
		}
	}

	
	if ( _controll ) {
		ClientPtr client = Client::getTask( );
		CLIENTDATA status = client->getClientData( );
		switch ( controll.action ) {
		case CONTROLL::NONE:
			if ( status.player[ _player_id ].action != ACTION_NONE ) {
				SERVERDATA data;
				data.command = COMMAND_STATUS_ACTION;
				data.value[ 0 ] = _player_id;
				data.value[ 1 ] = ACTION_NONE;
				client->send( data );	
			}
			break;
		case CONTROLL::ATTACK:
			if ( status.player[ _player_id ].action != ACTION_ATTACK ) {
				SERVERDATA data;
				data.command = COMMAND_STATUS_ACTION;
				data.value[ 0 ] = _player_id;
				data.value[ 1 ] = ACTION_ATTACK;
				client->send( data );	
			}
			break;
		}
	}
}


void PlayerWitchBehavior::animationUpdate( ) {
	if ( _wait_time > WAIT_MAX && _controll ) {
		AppPtr app = App::getTask( );
		AdventurePtr adventure = app->getAdventure( );
		adventure->set( Adventure::TYPE_WITCH_WAIT );
		_wait_time = 0;
	}
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
		_wait_time++;
	} else {
		_wait_time = 0;
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
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_DEATHBLOW, 0.5 ) );
		}
	}
	if ( _player_state == PLAYER_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_WITCH_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WITCH_DEAD ) );
		}
	}
}
