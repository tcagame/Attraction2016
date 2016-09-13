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
#include "Field.h"
#include "Effect.h"

PlayerMonkBehavior::PlayerMonkBehavior( unsigned char player_id ) :
PlayerBehavior( PLAYER_MONK, player_id ) {
}


PlayerMonkBehavior::~PlayerMonkBehavior( ) {
}

void PlayerMonkBehavior::attack( const CONTROLL& controll ) {
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	BulletPtr bullet;
	if ( !isDeathblow( ) && _attack_pattern == 0 ) {
		_target.reset( );
	}
	//ïKéEãZÇÃç\Ç¶
	PlayerPtr player = std::dynamic_pointer_cast< Player >( _parent );
	player->addSP( 100 );
	//ó≠ÇﬂÉÇÅ[ÉVÉáÉì
	if ( controll.action == CONTROLL::DEATHBLOW && ( _before_state == PLAYER_STATE_WAIT || _before_state == PLAYER_STATE_WALK || _before_state == PLAYER_STATE_ATTACK ) && player->getSP( ) == 100 ) {
		Effect effect;
		int id = effect.setEffect( Effect::EFFECT_PLAYER_MONK_STORE );
		effect.drawEffect( id, Vector( 0.3, 0.3, 0.3 ), _parent->getPos( ),_parent->getDir( ) );
		_player_state = PLAYER_STATE_STORE;
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
		bullet = BulletPtr( new BulletRush( _parent->getPos( ), _parent->getDir( ) ) );
		weapon->add( bullet );
		player->resetSP( );
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	//ïKéEãZèIóπÇ‹Ç≈ïKéEãZÉÇÅ[ÉVÉáÉì
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_MONK_DEATHBLOW && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_DEATHBLOW;
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
					bullet = BulletJabPtr( new BulletJab( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
					break;																									 
				case 1:																										 
					bullet = BulletImpactPtr( new BulletImpact( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
					break;																									 
				case 2:																										 
					bullet = BulletUpperPtr( new BulletUpper( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ) ) );
					break;
			}
			weapon->add( bullet );
			_player_state = PLAYER_STATE_ATTACK;
		}
	}
}

void PlayerMonkBehavior::animationUpdate( ) {
	if ( _player_state == PLAYER_STATE_DEAD && _animation->isEndAnimation( ) ) {
		_parent->dead( );
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