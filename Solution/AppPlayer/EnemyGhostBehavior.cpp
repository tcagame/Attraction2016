#include "EnemyGhostBehavior.h"
#include "Character.h"
#include "Animation.h"
#include "App.h"
#include "Player.h"

const double MOTION_SPEED = 0.5;

EnemyGhostBehavior::EnemyGhostBehavior( ) {
	_move_range = 5.5;
}

EnemyGhostBehavior::~EnemyGhostBehavior( ) {
}

void EnemyGhostBehavior::update( ) {
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
}

void EnemyGhostBehavior::movePosToTarget( ) {
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

void EnemyGhostBehavior::switchStatus( ) {
	_common_state = COMMON_STATE_WAIT;

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
}

void EnemyGhostBehavior::animationUpdate( ) {
	if ( _common_state == COMMON_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GHOST_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GHOST_WAIT, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _common_state == COMMON_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GHOST_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GHOST_WALK, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}	
}