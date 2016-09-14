#include "EtudeBehavior.h"
#include "Animation.h"
#include "Character.h"
#include "App.h"
#include "Player.h"
#include "Effect.h"
#include "Client.h"
#include "BulletDash.h"
#include "BulletCleave.h"
#include "BulletSmash.h"
#include "Weapon.h"

EtudeBehavior::EtudeBehavior( unsigned char etude_type, unsigned char player_id ) :
PlayerBehavior( etude_type, player_id ) {
}


EtudeBehavior::~EtudeBehavior()
{
}

void EtudeBehavior::attack( const CONTROLL& controll ) {
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );

	BulletPtr bullet;

	//UŒ‚‚É“ü‚éuŠÔ
	bool in_attack = controll.action == CONTROLL::ATTACK && _before_state != PLAYER_STATE_ATTACK;
	bool next_attack = false;
	//UŒ‚’†
	if ( ( _animation->getMotion( ) == Animation::MOTION_MINOTAUR_CLEAVE ||
			_animation->getMotion( ) == Animation::MOTION_MINOTAUR_SMASH ||
			_animation->getMotion( ) == Animation::MOTION_MINOTAUR_DASH ) ) {
		if ( !_animation->isEndAnimation( ) ) {
			_player_state = PLAYER_STATE_ATTACK;
		}
		if ( _animation->getEndAnimTime( ) - 15 < _animation->getAnimTime( ) && controll.action == CONTROLL::ATTACK ) {
			_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//UŒ‚ƒpƒ^[ƒ“‚Ì•ÏX
			_animation = AnimationPtr( new Animation( Animation::MOTION_MINOTAUR_WAIT ) );//ˆê’U‚v‚`‚h‚s‚É‚µ‚Ä‚¨‚­
			next_attack = true;
		}
	}
	if ( in_attack || next_attack ) {
		switch ( _attack_pattern ) {
			case 0:
				bullet = BulletPtr( new BulletDash( _parent->getPos( ), _parent->getDir( ) ) );
				break;
			case 1:
				bullet = BulletPtr( new BulletSmash( _parent->getPos( ), _parent->getDir( ) ) );
				break;
			case 2:
				bullet = BulletPtr( new BulletCleave( _parent->getPos( ), _parent->getDir( ).x, _parent->getDir( ).y ) );
				break;
		}
		weapon->add( bullet );
		_player_state = PLAYER_STATE_ATTACK;
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


void EtudeBehavior::animationUpdate( ) {
	if ( _player_state == PLAYER_STATE_DEAD && _animation->isEndAnimation( ) ) {
		_parent->dead( );
		return;
	}

	if ( _player_state == PLAYER_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_MINOTAUR_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_MINOTAUR_WAIT ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_MINOTAUR_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_MINOTAUR_WALK ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_MINOTAUR_CLEAVE &&
			 _animation->getMotion( ) != Animation::MOTION_MINOTAUR_SMASH&&
			 _animation->getMotion( ) != Animation::MOTION_MINOTAUR_DASH ) {
			switch ( _attack_pattern ) {
				case 0:
					_animation = AnimationPtr( new Animation( Animation::MOTION_MINOTAUR_DASH ) );
					break;
				case 1:
					_animation = AnimationPtr( new Animation( Animation::MOTION_MINOTAUR_SMASH ) );
					_animation->setAnimationTime( 40 );
					break;
				case 2:
					_animation = AnimationPtr( new Animation( Animation::MOTION_MINOTAUR_CLEAVE ) );
					_animation->setAnimationTime( 10 );
					break;
			}
		}
	}
	if ( _player_state == PLAYER_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_MINOTAUR_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_MINOTAUR_DEAD ) );
		}
	}
}