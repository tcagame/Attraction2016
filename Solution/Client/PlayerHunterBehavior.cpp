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
#include "Adventure.h"
#include "Client.h"

const int WAIT_MAX = 600;

PlayerHunterBehavior::PlayerHunterBehavior( unsigned char player_id ) :
PlayerBehavior( PLAYER_HUNTER, player_id ) {
	_wait_time = 0;
}


PlayerHunterBehavior::~PlayerHunterBehavior( ) {
}

void PlayerHunterBehavior::attack( const CONTROLL& controll ) {
	SoundPtr sound = Sound::getTask( );

	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	BulletPtr bullet;
	//必殺技の構え
	PlayerPtr player = std::dynamic_pointer_cast< Player >( _parent );
	int power = _parent->getStatus( ).power;
	//溜めモーション
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
			//AdventurePtr adventure = app->getAdventure( );
			//adventure->set( Adventure::TYPE_HUNTER_STORE );
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
	//溜め持続
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_STORE && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_STORE;
	}
	//必殺技をうつ
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_STORE && _animation->isEndAnimation( ) ) {
		bullet = BulletPtr( new BulletBulletRain( _parent->getPos( ), _parent->getDir( ), power ) );
		weapon->add( bullet );
		player->resetSP( );
		//AdventurePtr adventure = app->getAdventure( );
		//adventure->set( Adventure::TYPE_HUNTER_DEATHBLOW );
		sound->playSE( Sound::SE_HUNTER_DEATHBLOW );
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	//必殺技終了まで必殺技モーション
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_DEATHBLOW && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_DEATHBLOW && _animation->isEndAnimation( ) ) {
		sound->playSE( Sound::SE_HUNTER_DEATHBLOW_FINISH );
	}

	if ( !isDeathblow( ) ) {
		//攻撃に入る瞬間
		bool in_attack = controll.action == CONTROLL::ATTACK && _before_state != PLAYER_STATE_ATTACK;
		bool next_attack = false;
		//攻撃中
		if ( ( _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_ATTACK_FIRE ||
			  _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_ATTACK_RAPIDFIRE ||
			  _animation->getMotion( ) == Animation::MOTION_PLAYER_HUNTER_ATTACK_SHOT ) ) {
			if ( !_animation->isEndAnimation( ) ) {
				if ( _animation->getAnimTime( ) == 30.0 ) {
				switch ( _attack_pattern ) {
						case 0:
							sound->playSE( Sound::SE_HUNTER_ATTACK_1 );
							bullet = BulletFirePtr( new BulletFire( _parent->getPos( ), _parent->getDir( ), power ) );
							break;
						case 1:
							sound->playSE( Sound::SE_HUNTER_ATTACK_1 );
							bullet = BulletRapidFirePtr( new BulletRapidFire( _parent->getPos( ), _parent->getDir( ), power ) );
							break;
						case 2:
							sound->playSE( Sound::SE_HUNTER_ATTACK_2 );
							bullet = BulletShotPtr( new BulletShot( _parent->getPos( ), _parent->getDir( ), power ) );
							break;
					}
					weapon->add( bullet );
				}
				_player_state = PLAYER_STATE_ATTACK;
			}
			if ( _animation->getEndAnimTime( ) - 20 < _animation->getAnimTime( ) && controll.action == CONTROLL::ATTACK ) {
				_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//攻撃パターンの変更
				_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_HUNTER_WAIT ) );//一旦ＷＡＩＴにしておく
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
					effect_pos = _parent->getPos( ) + _parent->getDir( ) * 1.2 * Bullet::BULLET_SCALE + Vector( 0, 0, 1 ) * 1.2 * Bullet::BULLET_SCALE;
					effect.drawEffect( id, Vector( 0.05, 0.05, 0.05 ), effect_pos, _parent->getDir( )  );
					break;
				case 1:
					id = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_RAPID_FIRE );
					effect_pos = _parent->getPos( ) + _parent->getDir( ) * Bullet::BULLET_SCALE + Vector( 0, 0, 1 ) * Bullet::BULLET_SCALE;
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
	AppPtr app = App::getTask( );
	//AdventurePtr adventure = app->getAdventure( );
	if ( _wait_time > WAIT_MAX && _controll ) {
		//adventure->set( Adventure::TYPE_HUNTER_WAIT );
		_wait_time = 0;
	}
	if ( _player_state == PLAYER_STATE_DEAD && _animation->isEndAnimation( ) ) {
		_parent->dead( );
		if ( _controll ) {
			//adventure->set( Adventure::TYPE_COMMON_PLAYER_DEAD );
			//adventure->set( Adventure::TYPE_HUNTER_DEAD );
		}
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
		_wait_time++;
	} else {
		_wait_time = 0;
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
					_animation->setAnimationTime( 20 );
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