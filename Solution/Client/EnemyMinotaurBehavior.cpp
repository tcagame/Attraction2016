#include "EnemyMinotaurBehavior.h"
#include "Character.h"
#include "Animation.h"
#include "App.h"
#include "Player.h"

const double MOTION_SPEED = 1;
const double ATTACK_TIME = 27.0;

EnemyMinotaurBehavior::EnemyMinotaurBehavior( ) {
	_attack_range = 2.0;
	_move_range =7.5;
	_on_damage = false;

	_befor_hp = -1;
}

EnemyMinotaurBehavior::~EnemyMinotaurBehavior( ) {
}

void EnemyMinotaurBehavior::update( ) {
	searchTarget( );
	movePosToTarget( );
	switchStatus( );
	_before_state = _enemy_state;
	_befor_hp = _parent->getStatus( ).hp;
}

void EnemyMinotaurBehavior::searchTarget( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayerTarget( _parent->getPos( ) );
	if ( !player ) {
		_target.reset( );
	} else if ( player->isExpired( ) ) {
		_target = player;
	} else {
		_target.reset( );
	}
}

void EnemyMinotaurBehavior::movePosToTarget( ) {
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

void EnemyMinotaurBehavior::switchStatus( ) {
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
	//�U����
	if ( _animation->getMotion( ) == Animation::MOTION_MINOTAUR_CLEAVE && !_animation->isEndAnimation( ) ) {
		_enemy_state = ENEMY_STATE_ATTACK;
	}

	if ( _befor_hp > _parent->getStatus( ).hp ) {
		_on_damage = true;
	}

	if ( _parent->getStatus( ).hp <= 0 ) {
		_enemy_state = ENEMY_STATE_DEAD;
	}
}

void EnemyMinotaurBehavior::animationUpdate( ) {
	if ( _animation->getMotion( ) == Animation::MOTION_MINOTAUR_DEAD ) {
		if ( _animation->isEndAnimation( ) ) {
			_parent->dead( );
		}
		return;
	}
	if ( _animation->getMotion( ) == Animation::MOTION_MINOTAUR_DAMAGE && !_animation->isEndAnimation( ) ) {
		_enemy_state = ENEMY_STATE_WAIT;
		return;
	}
	if ( _enemy_state == ENEMY_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_MINOTAUR_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_MINOTAUR_WAIT, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _enemy_state == ENEMY_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_MINOTAUR_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_MINOTAUR_WALK, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _enemy_state == ENEMY_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_MINOTAUR_CLEAVE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_MINOTAUR_CLEAVE, MOTION_SPEED ) );
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
		if ( _animation->getMotion( ) != Animation::MOTION_MINOTAUR_DAMAGE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_MINOTAUR_DAMAGE, MOTION_SPEED ) );
		}
	}
	if ( _enemy_state == ENEMY_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_MINOTAUR_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_MINOTAUR_DEAD, MOTION_SPEED ) );
		}
	}
}

void EnemyMinotaurBehavior::onAttack( ) {

	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayerMine( );
	if ( !player ) {
		return;
	}
	Vector target_pos = player->getPos( );
	Vector stance = target_pos - _parent->getPos( );

	double range = stance.getLength( );
	
	if ( range <= _attack_range ) {
		player->damage( _parent->getStatus( ).power );
	}
}
