#include "EnemyGoblinBehavior.h"
#include "Character.h"
#include "Animation.h"
#include "Sound.h"
#include "Effect.h"
#include "App.h"
#include "Player.h"

const double MOTION_SPEED = 1;
const double ATTACK_TIME = 27.0;
const double DAMAGE_SCALE = 0.3;

EnemyGoblinBehavior::EnemyGoblinBehavior() {
	_attack_range = 1.0;
	_move_range =7.5;
	_on_damage = false;

	_befor_hp = -1;
}

EnemyGoblinBehavior::~EnemyGoblinBehavior() {
}

void EnemyGoblinBehavior::update( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayerMine( );
	if ( player->isExpired( ) ) {
		_target = player;
	} else {
		_target.reset( );
	}

	movePosToTarget( );
	switchStatus( );
	_before_state = _enemy_state;
	_befor_hp = _parent->getStatus( ).hp;
}

void EnemyGoblinBehavior::movePosToTarget( ) {
	if ( _target.expired( ) ) {
		return;
	}
	PlayerPtr player = _target.lock( );
	Vector target_pos = player->getPos( );
	
	Vector distance = target_pos - _parent->getPos( );
	double length = distance.getLength( );
	if ( _enemy_state == ENEMY_STATE_WALK ) {
		_parent->move( distance * _parent->getStatus( ).speed );
	}
}

void EnemyGoblinBehavior::switchStatus( ) {
	_enemy_state = ENEMY_STATE_WAIT;
	_on_damage = false;

	if ( _target.expired( ) ) {
		return;
	}
	PlayerPtr player = _target.lock( );
	Vector target_pos = player->getPos( );
	Vector stance = target_pos - _parent->getPos( );
	double range = stance.getLength( );
	if ( range <= _move_range ) {
		_enemy_state = ENEMY_STATE_WALK;
	}

	if ( range <= _attack_range && _before_state != ENEMY_STATE_ATTACK ) {
		_enemy_state = ENEMY_STATE_ATTACK;
	}
	//UŒ‚’†
	if ( _animation->getMotion( ) == Animation::MOTION_GOBLIN_ATTACK && !_animation->isEndAnimation( ) ) {
		_enemy_state = ENEMY_STATE_ATTACK;
	}

	if ( _befor_hp > _parent->getStatus( ).hp ) {
		_on_damage = true;
		Effect effect;
		int damage_effect = effect.setEffect( Effect::EFFECT_DAMAGE );
		effect.drawEffect( damage_effect, Vector( DAMAGE_SCALE, DAMAGE_SCALE, DAMAGE_SCALE ), _parent->getPos( ), _parent->getDir( ) );
	}

	if ( _parent->getStatus( ).hp <= 0 ) {
		_enemy_state = ENEMY_STATE_DEAD;
	}
}

void EnemyGoblinBehavior::animationUpdate( ) {
	if ( _animation->getMotion( ) == Animation::MOTION_GOBLIN_DEAD ) {
		if ( _animation->isEndAnimation( ) ) {
			_parent->dead( );
		}
		return;
	}
	if ( _animation->getMotion( ) == Animation::MOTION_GOBLIN_DAMAGE && !_animation->isEndAnimation( ) ) {
		_enemy_state = ENEMY_STATE_WAIT;
		return;
	}
	if ( _enemy_state == ENEMY_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GOBLIN_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GOBLIN_WAIT, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _enemy_state == ENEMY_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GOBLIN_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GOBLIN_WALK, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _enemy_state == ENEMY_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GOBLIN_ATTACK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GOBLIN_ATTACK, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
			if ( _animation->getAnimTime( ) == ATTACK_TIME ) {
				onAttack( );
			}
		}
	}
	if ( _on_damage ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GOBLIN_DAMAGE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GOBLIN_DAMAGE, MOTION_SPEED ) );
		}
	}
	if ( _enemy_state == ENEMY_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GOBLIN_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GOBLIN_DEAD, MOTION_SPEED ) );
		}
	}
}

void EnemyGoblinBehavior::onAttack( ) {
	AppPtr app = App::getTask( );
	SoundPtr sound = Sound::getTask( );
	sound->playSE( Sound::SE_ENEMY_ATTACK );
	PlayerPtr player = app->getPlayerMine( );
	Vector player_pos = player->getPos( );
	Vector pos = _parent->getPos( );
	Vector vec = player_pos - pos;
	Vector dir = vec.normalize( );
	Vector attack_pos = pos +  dir * 1.5;
	Vector smash_dis = attack_pos - player_pos;

	if ( smash_dis.getLength( ) < 0.5 ) {
		player->damage( _parent->getStatus( ).power );
	}
}