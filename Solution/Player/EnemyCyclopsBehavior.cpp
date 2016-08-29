#include "EnemyCyclopsBehavior.h"
#include "Character.h"
#include "Animation.h"
#include "App.h"
#include "Player.h"

const double MOTION_SPEED = 1;
const double ATTACK_TIME = 27.0;

EnemyCyclopsBehavior::EnemyCyclopsBehavior() {
	_attack_range = 2.0;
	_move_range =7.5;
	_on_damage = false;

	_befor_hp = -1;
}

EnemyCyclopsBehavior::~EnemyCyclopsBehavior( ) {
}


void EnemyCyclopsBehavior::update( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );
	if ( player->isExpired( ) ) {
		_target = player;
	} else {
		_target.reset( );
	}

	movePosToTarget( );
	switchStatus( );
	_befor_state = _common_state;
	_befor_hp = _parent->getStatus( ).hp;
}

void EnemyCyclopsBehavior::movePosToTarget( ) {
	if ( _target.expired( ) ) {
		return;
	}
	PlayerPtr player = _target.lock( );
	Vector target_pos = player->getPos( );
	
	Vector distance = target_pos - _parent->getPos( );
	double length = distance.getLength( );
	if ( _common_state == COMMON_STATE_WALK ) {
		_parent->move( distance * _parent->getStatus( ).speed );
	}
}

void EnemyCyclopsBehavior::switchStatus( ) {
	_common_state = COMMON_STATE_WAIT;
	_on_damage = false;

	if ( _target.expired( ) ) {
		return;
	}
	PlayerPtr player = _target.lock( );
	Vector target_pos = player->getPos( );
	Vector stance = target_pos - _parent->getPos( );
	double range = stance.getLength( );
	if ( range <= _move_range ) {
		_common_state = COMMON_STATE_WALK;
	}

	if ( range <= _attack_range && _befor_state != COMMON_STATE_ATTACK ) {
		_common_state = COMMON_STATE_ATTACK;
	}
	//UŒ‚’†
	if ( _animation->getMotion( ) == Animation::MOTION_CYCLOPS_ATTACK && !_animation->isEndAnimation( ) ) {
		_common_state = COMMON_STATE_ATTACK;
	}

	if ( _befor_hp > _parent->getStatus( ).hp ) {
		_on_damage = true;
	}

	if ( _parent->getStatus( ).hp <= 0 ) {
		_common_state = COMMON_STATE_DEAD;
	}
}

void EnemyCyclopsBehavior::animationUpdate( ) {
	if ( _animation->getMotion( ) == Animation::MOTION_CYCLOPS_DEAD ) {
		if ( _animation->isEndAnimation( ) ) {
			_parent->dead( );
		}
		return;
	}
	if ( _animation->getMotion( ) == Animation::MOTION_CYCLOPS_DAMAGE && !_animation->isEndAnimation( ) ) {
		_common_state = COMMON_STATE_WAIT;
		return;
	}
	if ( _common_state == COMMON_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_CYCLOPS_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_CYCLOPS_WAIT, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_CYCLOPS_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_CYCLOPS_WALK, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_CYCLOPS_ATTACK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_CYCLOPS_ATTACK, MOTION_SPEED ) );
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
		if ( _animation->getMotion( ) != Animation::MOTION_CYCLOPS_DAMAGE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_CYCLOPS_DAMAGE, MOTION_SPEED ) );
		}
	}
	if ( _common_state == COMMON_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_CYCLOPS_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_CYCLOPS_DEAD, MOTION_SPEED ) );
		}
	}
}

void EnemyCyclopsBehavior::onAttack( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );
	player->damage( _parent->getStatus( ).power );
}