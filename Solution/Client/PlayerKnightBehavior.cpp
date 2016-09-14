#include "PlayerKnightBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "App.h"
#include "BulletSword.h"
#include "BulletSlash.h"
#include "BulletStab.h"
#include "BulletExcalibur.h"
#include "Weapon.h"
#include "Player.h"
#include "Sound.h"
#include "Effect.h"
#include "Adventure.h"
#include "Client.h"

const int WAIT_MAX = 300;

PlayerKnightBehavior::PlayerKnightBehavior( unsigned char player_id ) :
PlayerBehavior( PLAYER_KNIGHT, player_id ) {
}

PlayerKnightBehavior::~PlayerKnightBehavior( ) {
}

void PlayerKnightBehavior::attack( const CONTROLL& controll ) {
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	BulletPtr bullet;
	SoundPtr sound = Sound::getTask( );
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
			effect.drawEffect( id, Vector( 0.3, 0.3, 0.3 ), _parent->getPos( ) + Vector( 0, 0, 0.5 ),_parent->getDir( ) );
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
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_STORE && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_STORE;
	}
	//ïKéEãZÇÇ§Ç¬
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_STORE && _animation->isEndAnimation( ) ) {
		bullet = BulletPtr( new BulletExcalibur( _parent->getPos( ), _parent->getDir( ) ) );
		weapon->add( bullet );
		player->resetSP( );
		_player_state = PLAYER_STATE_DEATHBLOW;
		sound->playSE( Sound::SE_KNIGHT_DEATHBLOW );
	}
	//ïKéEãZèIóπÇ‹Ç≈ïKéEãZÉÇÅ[ÉVÉáÉì
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_DEATHBLOW && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_DEATHBLOW && _animation->isEndAnimation( ) ) {
		sound->playSE( Sound::SE_KNIGHT_DEATHBLOW_FINISH );
	}

	if ( !isDeathblow( ) ) {
		//çUåÇÇ…ì¸ÇÈèuä‘
		bool in_attack = controll.action == CONTROLL::ATTACK && _before_state != PLAYER_STATE_ATTACK;
		bool next_attack = false;
		//çUåÇíÜ
		if ( ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_ATTACK_SLASH ||
			  _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_ATTACK_SWORD ||
			  _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_ATTACK_STAB ) ) {
			if ( !_animation->isEndAnimation( ) ) {
				_player_state = PLAYER_STATE_ATTACK;
			}
			if ( _animation->getEndAnimTime( ) - 15 < _animation->getAnimTime( ) && controll.action == CONTROLL::ATTACK ) {
				_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//çUåÇÉpÉ^Å[ÉìÇÃïœçX
				_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_WAIT ) );//àÍíUÇvÇ`ÇhÇsÇ…ÇµÇƒÇ®Ç≠
				next_attack = true;
			}
		}
		if ( in_attack || next_attack ) {
			switch ( _attack_pattern ) {
				case 0:
					sound->playSE( Sound::SE_KNIGHT_ATTACK_1 );
					bullet = BulletSlashPtr( new BulletSlash( _parent->getPos( ), _parent->getDir( ).x, _parent->getDir( ).y ) );
					break;
				case 1:
					sound->playSE( Sound::SE_KNIGHT_ATTACK_2 );
					bullet = BulletSwordPtr( new BulletSword( _parent->getPos( ), _parent->getDir( ).x, _parent->getDir( ).y ) );
					break;
				case 2:
					sound->playSE( Sound::SE_KNIGHT_ATTACK_3 );
					bullet = BulletStabPtr( new BulletStab( _parent->getPos( ), _parent->getDir( ).x, _parent->getDir( ).y ) );
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

void PlayerKnightBehavior::animationUpdate( ) {
	if ( _wait_time > WAIT_MAX && _controll ) {
		AppPtr app = App::getTask( );
		AdventurePtr adventure = app->getAdventure( );
		adventure->start( Adventure::TYPE_KNIGHT_WAIT );
		_wait_time = 0;
	}

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
		_wait_time++;
	} else {
		_wait_time = 0;
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
					_animation->setAnimationTime( 10 );
					break;
				case 2:
					_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_ATTACK_STAB, 2.0 ) );
					_animation->setAnimationTime( 10 );
					break;
			}
		}
	}
	if ( _player_state == PLAYER_STATE_STORE ) {
		if ( _animation->getMotion( ) != Animation::MOTION_PLAYER_KNIGHT_STORE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_STORE, 0.25 ) );
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