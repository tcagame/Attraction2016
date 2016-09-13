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
#include "Effect.h"

PlayerKnightBehavior::PlayerKnightBehavior( unsigned char player_id ) :
PlayerBehavior( PLAYER_KNIGHT, player_id ) {
}

PlayerKnightBehavior::~PlayerKnightBehavior( ) {
}

void PlayerKnightBehavior::attack( const CONTROLL& controll ) {
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	BulletPtr bullet;
	
	//必殺技の構え
	PlayerPtr player = std::dynamic_pointer_cast< Player >( _parent );
	player->addSP( 100 );
	//溜めモーション
	if ( controll.action == CONTROLL::DEATHBLOW && ( _before_state == PLAYER_STATE_WAIT || _before_state == PLAYER_STATE_WALK || _before_state == PLAYER_STATE_ATTACK ) && player->getSP( ) == 100 ) {
		Effect effect;
		int id = effect.setEffect( Effect::EFFECT_PLAYER_HUNTER_STORE );
		effect.drawEffect( id, Vector( 0.3, 0.3, 0.3 ), _parent->getPos( ) + Vector( 0, 0, 0.5 ),_parent->getDir( ) );
		_player_state = PLAYER_STATE_STORE;
	}
	//溜め持続
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_STORE && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_STORE;
	}
	//必殺技をうつ
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_STORE && _animation->isEndAnimation( ) ) {
		bullet = BulletPtr( new BulletExcalibur( _parent->getPos( ), _parent->getDir( ) ) );
		weapon->add( bullet );
		player->resetSP( );
		_player_state = PLAYER_STATE_DEATHBLOW;
	}
	//必殺技終了まで必殺技モーション
	if ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_DEATHBLOW && !_animation->isEndAnimation( ) ) {
		_player_state = PLAYER_STATE_DEATHBLOW;
	}

	if ( !isDeathblow( ) ) {
		//攻撃に入る瞬間
		bool in_attack = controll.action == CONTROLL::ATTACK && _before_state != PLAYER_STATE_ATTACK;
		bool next_attack = false;
		//攻撃中
		if ( ( _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_ATTACK_SLASH ||
			  _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_ATTACK_SWORD ||
			  _animation->getMotion( ) == Animation::MOTION_PLAYER_KNIGHT_ATTACK_STAB ) ) {
			if ( !_animation->isEndAnimation( ) ) {
				_player_state = PLAYER_STATE_ATTACK;
			}
			if ( _animation->getEndAnimTime( ) - 15 < _animation->getAnimTime( ) && controll.action == CONTROLL::ATTACK ) {
				_attack_pattern = ( _attack_pattern + 1 ) % MAX_ATTACK_PATTERN;//攻撃パターンの変更
				_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_KNIGHT_WAIT ) );//一旦ＷＡＩＴにしておく
				next_attack = true;
			}
		}
		if ( in_attack || next_attack ) {
			switch ( _attack_pattern ) {
				case 0:
					bullet = BulletSlashPtr( new BulletSlash( _parent->getPos( ), _parent->getDir( ).x, _parent->getDir( ).y ) );
					break;
				case 1:
					bullet = BulletSwordPtr( new BulletSword( _parent->getPos( ), _parent->getDir( ).x, _parent->getDir( ).y ) );
					break;
				case 2:
					bullet = BulletStabPtr( new BulletStab( _parent->getPos( ), _parent->getDir( ).x, _parent->getDir( ).y ) );
					break;
			}
			weapon->add( bullet );
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