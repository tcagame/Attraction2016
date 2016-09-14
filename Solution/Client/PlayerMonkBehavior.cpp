#include "PlayerMonkBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "App.h"
#include "BulletJab.h"
#include "BulletImpact.h"
#include "BulletUpper.h"
#include "BulletRush.h"
#include "Weapon.h"
#include "Player.h"
#include "Sound.h"
#include "Field.h"
#include "Effect.h"
#include "Client.h"
#include "Adventure.h"

const int WAIT_MAX = 600;

PlayerMonkBehavior::PlayerMonkBehavior( unsigned char player_id ) :
PlayerBehavior( PLAYER_MONK, player_id ) {
	_wait_time = 0;
}


PlayerMonkBehavior::~PlayerMonkBehavior( ) {
}

void PlayerMonkBehavior::attack( const CONTROLL& controll ) {
	SoundPtr sound = Sound::getTask( );
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	BulletPtr bullet;
	if ( !isDeathblow( ) && _attack_pattern == 0 ) {
		_target.reset( );
	}
	//ïKéEãZÇÃç\Ç¶
	PlayerPtr player = std::dynamic_pointer_cast< Player >( _parent );
	int power = _parent->getStatus( ).power;
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
			int id = effect.setEffect( Effect::EFFECT_PLAYER_MONK_STORE );
			effect.drawEffect( id, Vector( 0.3, 0.3, 0.3 ), _parent->getPos( ),_parent->getDir( ) );
			_player_state = PLAYER_STATE_STORE;
			sound->playSE( Sound::SE_PLAYER_STORE );
			//AdventurePtr adventure = app->getAdventure( );
			//adventure->set( Adventure::TYPE_MONK_STORE );
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
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_MONK_STORE && !_animation->isEndAnimation( ) ) {
		FieldPtr field = app->getField( );
		Vector pos = _parent->getPos( ) + _parent->getDir( );
		CharacterPtr character = std::dynamic_pointer_cast< Character >( field->getTarget( ( int )pos.x, ( int )pos.y ) );
		if ( character ) {
			_target = character;
		}
		_player_state = PLAYER_STATE_STORE;
	}
	//ïKéEãZÇÇ§Ç¬
	bool isEnemy = false;
	if ( !_target.expired( ) ) {
		CharacterPtr character = _target.lock( );
		isEnemy = character->getType( ) == Character::TYPE_ENEMY;
	}
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_MONK_STORE && _animation->isEndAnimation( ) && isEnemy ) {
		bullet = BulletPtr( new BulletRush( _parent->getPos( ), _parent->getDir( ), power ) );
		weapon->add( bullet );
		player->resetSP( );
		sound->playSE( Sound::SE_MONK_ATTACK_2 );
		sound->playSE( Sound::SE_MONK_ATTACK_1 );
		//AdventurePtr adventure = app->getAdventure( );
		//adventure->set( Adventure::TYPE_MONK_DEATHBLOW );
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	//ïKéEãZèIóπÇ‹Ç≈ïKéEãZÉÇÅ[ÉVÉáÉì
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_MONK_DEATHBLOW && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_MONK_DEATHBLOW && _animation->isEndAnimation( ) ) {
		sound->playSE( Sound::SE_MONK_DEATHBLOW_FINISH );
	}

	if ( !isDeathblow( ) ) {
		bool in_attack = controll.action == CONTROLL::ATTACK && _before_state != PLAYER_STATE_ATTACK;
		bool next_attack = false;
		//çUåÇíÜ
		if ( ( _animation->getMotion( ) == Animation::MOTION_PLAYER_MONK_ATTACK_JAB || 
				_animation->getMotion( ) == Animation::MOTION_PLAYER_MONK_ATTACK_IMPACT || 
				_animation->getMotion( ) == Animation::MOTION_PLAYER_MONK_ATTACK_UPPER ) ) {
			if ( !_animation->isEndAnimation( ) ) {
				_player_state = PLAYER_STATE_ATTACK;
			}
			if ( _animation->getEndAnimTime( ) - 15 < _animation->getAnimTime( ) && controll.action == CONTROLL::ATTACK ) {
				_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//çUåÇÉpÉ^Å[ÉìÇÃïœçX
				_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_WAIT ) );//àÍíUÇvÇ`ÇhÇsÇ…ÇµÇƒÇ®Ç≠
				next_attack = true;
			}
		}

		if ( in_attack || next_attack ) {
			switch ( _attack_pattern ) {
				case 0:
					sound->playSE( Sound::SE_MONK_ATTACK_1 );
					bullet = BulletJabPtr( new BulletJab( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ), power ) );
					break;																									 
				case 1:					
					sound->playSE( Sound::SE_MONK_ATTACK_2 );
					bullet = BulletImpactPtr( new BulletImpact( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ), power ) );
					break;																									 
				case 2:										
					sound->playSE( Sound::SE_MONK_ATTACK_3 );
					bullet = BulletUpperPtr( new BulletUpper( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ), power ) );
					break;
			}
			weapon->add( bullet );
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

void PlayerMonkBehavior::animationUpdate( ) {
	AppPtr app = App::getTask( );
	//AdventurePtr adventure = app->getAdventure( );
	if ( _wait_time > WAIT_MAX && _controll ) {
		//adventure->set( Adventure::TYPE_MONK_WAIT );
		_wait_time = 0;
	}

	if ( _player_state == PLAYER_STATE_DEAD && _animation->isEndAnimation( ) ) {
		_parent->dead( );
		if ( _controll ) {
			//adventure->set( Adventure::TYPE_COMMON_PLAYER_DEAD );
			//adventure->set( Adventure::TYPE_MONK_DEAD );
		}
		return;
	}

	if ( _player_state == PLAYER_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_MONK_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_WAIT ) );
		} else {
			if( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
		_wait_time++;
	} else {
		_wait_time = 0;
	}
	if ( _player_state == PLAYER_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_MONK_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_WALK ) ); 
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_MONK_ATTACK_JAB && 
			 _animation->getMotion( ) != Animation::MOTION_PLAYER_MONK_ATTACK_IMPACT && 
			 _animation->getMotion( ) != Animation::MOTION_PLAYER_MONK_ATTACK_UPPER ) {

			switch ( _attack_pattern ) {
				case 0:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_ATTACK_JAB, 1.5 ) );
					break;
				case 1:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_ATTACK_IMPACT ) );
					_animation->setAnimationTime( 10 );
					break;
				case 2:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_ATTACK_UPPER, 1.5 ) );
					_animation->setAnimationTime( 15 );
					break;
			}
		}
	}
	if ( _player_state == PLAYER_STATE_STORE ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_MONK_STORE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_STORE, 0.25 ) );
		}
	}
	if ( _player_state == PLAYER_STATE_DEATHBLOW ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_MONK_DEATHBLOW ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_DEATHBLOW ) );
		}
	}
	if ( _player_state == PLAYER_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_MONK_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_MONK_DEAD ) );
		}
	}
}