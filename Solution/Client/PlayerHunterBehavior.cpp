#include "PlayerHunterBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "App.h"
#include "BulletFire.h"
#include "BulletRapidFire.h"
#include "BulletShot.h"
#include "BulletBulletRain.h"
#include "Sound.h"
#include "Weapon.h"
#include "Player.h"
#include "Effect.h"
#include "Client.h"

PlayerHunterBehavior::PlayerHunterBehavior( unsigned char player_id ) :
PlayerBehavior( PLAYER_HUNTER, player_id ) {
}


PlayerHunterBehavior::~PlayerHunterBehavior( ) {
}

void PlayerHunterBehavior::attack( const CONTROLL& controll ) {
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
			effect.drawEffect( id, Vector( 0.5, 0.5, 0.5 ), _parent->getPos( ) + Vector( 0, 0, 0.5 ),_parent->getDir( ) );
			_player_state = PLAYER_STATE_STORE;
			sound->playSE( Sound::SE_PLAYER_STORE );
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
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_STORE && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_STORE;
	}
	//ïKéEãZÇÇ§Ç¬
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_STORE && _animation->isEndAnimation( ) ) {
		bullet = BulletPtr( new BulletBulletRain( _parent->getPos( ), _parent->getDir( ) ) );
		weapon->add( bullet );
		player->resetSP( );
		sound->playSE( Sound::SE_HUNTER_DEATHBLOW );
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	//ïKéEãZèIóπÇ‹Ç≈ïKéEãZÉÇÅ[ÉVÉáÉì
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_DEATHBLOW && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_DEATHBLOW && _animation->isEndAnimation( ) ) {
		sound->playSE( Sound::SE_HUNTER_DEATHBLOW_FINISH );
	}

	if ( !isDeathblow( ) ) {
		//çUåÇÇ…ì¸ÇÈèuä‘
		bool in_attack = controll.action == CONTROLL::ATTACK && _before_state != PLAYER_STATE_ATTACK;
		bool next_attack = false;
		//çUåÇíÜ
		if ( ( _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_ATTACK_FIRE ||
			  _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_ATTACK_RAPIDFIRE ||
			  _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_ATTACK_SHOT ) ) {
			if ( !_animation->isEndAnimation( ) ) {
				if ( _animation->getAnimTime( ) == 40.0 ) {
				switch ( _attack_pattern ) {
						case 0:
							sound->playSE( Sound::SE_HUNTER_ATTACK_1 );
							bullet = BulletFirePtr( new BulletFire( _parent->getPos( ), _parent->getDir( ) ) );
							break;
						case 1:
							sound->playSE( Sound::SE_HUNTER_ATTACK_1 );
							bullet = BulletRapidFirePtr( new BulletRapidFire( _parent->getPos( ), _parent->getDir( ) ) );
							break;
						case 2:
							sound->playSE( Sound::SE_HUNTER_ATTACK_2 );
							bullet = BulletShotPtr( new BulletShot( _parent->getPos( ), _parent->getDir( ) ) );
							break;
					}
					weapon->add( bullet );
				}
				_player_state = PLAYER_STATE_ATTACK;
			}
			if ( _animation->getEndAnimTime( ) - 20 < _animation->getAnimTime( ) && controll.action == CONTROLL::ATTACK ) {
				_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//çUåÇÉpÉ^Å[ÉìÇÃïœçX
				_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_WAIT ) );//àÍíUÇvÇ`ÇhÇsÇ…ÇµÇƒÇ®Ç≠
				next_attack = true;
			}
		}
		if ( in_attack || next_attack ) {
			Effect effect;
			int id;
			Vector effect_pos;
			switch ( _attack_pattern ) {
				case 0:
					id = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_FIRE );
					effect_pos = _parent->getPos( ) + _parent->getDir( ) * 0.5 + Vector( 0, 0, 0.5 );
					effect.drawEffect( id, Vector( 0.05, 0.05, 0.05 ), effect_pos, _parent->getDir( )  );
					break;
				case 1:
					id = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_RAPID_FIRE );
					effect_pos = _parent->getPos( ) + _parent->getDir( ) * 0.3 + Vector( 0, 0, 0.2 );
					effect.drawEffect( id, Vector( 0.05, 0.05, 0.05 ), effect_pos, _parent->getDir( )  );
					break;
				case 2:
					//id = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_SHOT );
					//effect_pos = _parent->getPos( ) + _parent->getDir( ) + Vector( 0, 0, 0.5 );
					//Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), PI / 2 );
					//effect.drawEffect( id, Vector( 0.1, 0.1, 0.1 ), effect_pos, mat.multiply( _parent->getDir( ) )  );
					break;
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

void PlayerHunterBehavior::animationUpdate( ) {
	if ( _player_state == PLAYER_STATE_DEAD && _animation->isEndAnimation( ) ) {
		_parent->dead( );
		return;
	}

	if ( _player_state == PLAYER_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_HUNTER_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_WAIT ) );
		} else {
			if( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_HUNTER_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_WALK ) ); 
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_HUNTER_ATTACK_FIRE &&
			 _animation->getMotion( ) != Animation::MOTION_PLAYER_HUNTER_ATTACK_SHOT &&
			 _animation->getMotion( ) != Animation::MOTION_PLAYER_HUNTER_ATTACK_RAPIDFIRE ) {
			switch ( _attack_pattern ) {
				case 0:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_ATTACK_FIRE ) );
					_animation->setAnimationTime( 10 );
					break;
				case 1:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_ATTACK_RAPIDFIRE ) );
					_animation->setAnimationTime( 10 ); 
					break;
				case 2:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_ATTACK_SHOT ) );
					_animation->setAnimationTime( 10 );
					break;
			}
		}
	}
	if ( _player_state == PLAYER_STATE_STORE ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_HUNTER_STORE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_STORE, 0.25 ) );
		}
	}
	if ( _player_state == PLAYER_STATE_DEATHBLOW ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_HUNTER_DEATHBLOW ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_DEATHBLOW ) );
		}
	}
	if ( _player_state == PLAYER_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_HUNTER_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_DEAD ) );
		}
	}
}