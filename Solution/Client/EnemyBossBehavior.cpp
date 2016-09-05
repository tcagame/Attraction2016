#include "EnemyBossBehavior.h"
#include "Character.h"
#include "Animation.h"
#include "App.h"
#include "Player.h"

const double MOTION_SPEED = 1;
const double ATTACK_TIME = 27.0;

const Animation::MOTION BOSS_ATTACK_MOTION[ ] = {
	Animation::MOTION::MOTION_BOSS_ATTACK_CLEAVE,	
	Animation::MOTION::MOTION_BOSS_ATTACK_BITE,	
	Animation::MOTION::MOTION_BOSS_ATTACK_FIRE,	
	Animation::MOTION::MOTION_BOSS_ATTACK_BOMBING
};

EnemyBossBehavior::EnemyBossBehavior() {
	_attack_range[ BOSS_ATTACK_PATTERN_CLEAVE ] = 1.0;
	_attack_range[ BOSS_ATTACK_PATTERN_BITE ] = 2.0;
	_attack_range[ BOSS_ATTACK_PATTERN_FIRE ] = 3.0;
	_attack_range[ BOSS_ATTACK_PATTERN_BOMBING ] = 4.0;
	_attack_pattern = BOSS_ATTACK_PATTERN_MAX;
	_on_damage = false;
	_befor_hp = -1;
}

EnemyBossBehavior::~EnemyBossBehavior() {
}

void EnemyBossBehavior::update( ) {
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

void EnemyBossBehavior::movePosToTarget( ) {
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

void EnemyBossBehavior::switchStatus( ) {
	_common_state = COMMON_STATE_WAIT;
	_on_damage = false;

	if ( _target.expired( ) ) {
		return;
	}
	PlayerPtr player = _target.lock( );
	Vector target_pos = player->getPos( );
	Vector stance = target_pos - _parent->getPos( );
	double range = stance.getLength( );
	for( int i = 0; i < BOSS_ATTACK_PATTERN_MAX; i++ ) {  
		if ( range <= _attack_range[ i ] && _befor_state != COMMON_STATE_ATTACK ) {
			_common_state = COMMON_STATE_ATTACK;
			_attack_pattern = i;
			break;
		}
		//UŒ‚’†
		if ( _animation->getMotion( ) == BOSS_ATTACK_MOTION[ i ] &&  !_animation->isEndAnimation( ) ) {
			_common_state = COMMON_STATE_ATTACK;
		}
	}
	
	/*if ( ( _animation->getMotion( ) == Animation::MOTION_BOSS_ATTACK_CLEAVE ||
		   _animation->getMotion( ) == Animation::MOTION_BOSS_ATTACK_BITE || 
		   _animation->getMotion( ) == Animation::MOTION_BOSS_ATTACK_FIRE || 
		   _animation->getMotion( ) == Animation::MOTION_BOSS_ATTACK_BOMBING ) &&
		 ) {
		
	}*/

	if ( _befor_hp > _parent->getStatus( ).hp ) {
		_on_damage = true;
	}

	if ( _parent->getStatus( ).hp <= 0 ) {
		_common_state = COMMON_STATE_DEAD;
	}
}

void EnemyBossBehavior::animationUpdate( ) {
	if ( _animation->getMotion( ) == Animation::MOTION_BOSS_DEAD ) {
		if ( _animation->isEndAnimation( ) ) {
			_parent->dead( );
		}
		return;
	}
	if ( _animation->getMotion( ) == Animation::MOTION_BOSS_DAMAGE && !_animation->isEndAnimation( ) ) {
		_common_state = COMMON_STATE_WAIT;
		return;
	}
	if ( _common_state == COMMON_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_BOSS_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_BOSS_WAIT, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_ATTACK ) {
		if( _animation->getMotion( ) != BOSS_ATTACK_MOTION[ _attack_pattern ] ) {
			_animation = AnimationPtr( new Animation( BOSS_ATTACK_MOTION[ _attack_pattern ], MOTION_SPEED ) );
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
		if ( _animation->getMotion( ) != Animation::MOTION_BOSS_DAMAGE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_BOSS_DAMAGE, MOTION_SPEED ) );
		}
	}
	if ( _common_state == COMMON_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_BOSS_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_BOSS_DEAD, MOTION_SPEED ) );
		}
	}
}

void EnemyBossBehavior::onAttack( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );
	player->damage( _parent->getStatus( ).power );
}