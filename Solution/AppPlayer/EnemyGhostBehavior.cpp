#include "EnemyGhostBehavior.h"
#include "Character.h"
#include "Animation.h"
#include "Weapon.h"
#include "BulletMissile.h"
#include "App.h"
#include "Player.h"

const double MOTION_SPEED = 0.5;
const int ATTACK_TIME = 40;

EnemyGhostBehavior::EnemyGhostBehavior( ) {
	_move_range = 5.5;
	_attack_range = 3.5;
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
	if ( range <= _attack_range && _befor_state != COMMON_STATE_ATTACK ) {
		_common_state = COMMON_STATE_ATTACK;
	}
		//UŒ‚’†
	if ( _animation->getMotion( ) == Animation::MOTION_GHOST_ATTACK && !_animation->isEndAnimation( ) ) {
		_common_state = COMMON_STATE_ATTACK;
		//ƒ_ƒ[ƒW
		if ( _animation->getAnimTime( ) == ATTACK_TIME ) {
			onAttack( );
		}
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
	if ( _common_state == COMMON_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GHOST_ATTACK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GHOST_ATTACK, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
}

void EnemyGhostBehavior::onAttack( ) {
	Vector dir = _parent->getDir( );
	Vector pos = _parent->getPos( );

	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	BulletMissilePtr bullet = BulletMissilePtr ( new BulletMissile( pos, dir ) );
	weapon->add( bullet );
}