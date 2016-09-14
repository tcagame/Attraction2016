#include "EnemyGhostBehavior.h"
#include "Character.h"
#include "Effect.h"
#include "Animation.h"
#include "Weapon.h"
#include "BulletFireBall.h"
#include "App.h"
#include "Player.h"

const double MOTION_SPEED = 1;
const int ATTACK_TIME = 40;
const double DAMAGE_SCALE = 0.5;

EnemyGhostBehavior::EnemyGhostBehavior( ) {
	_move_range = 6.0;
	_attack_range = 3.5;
	_on_damage = false;
	_before_hp = -1;
}

EnemyGhostBehavior::~EnemyGhostBehavior( ) {
}

void EnemyGhostBehavior::update( ) {
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
	_before_hp = _parent->getStatus( ).hp;
}

void EnemyGhostBehavior::movePosToTarget( ) {
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

void EnemyGhostBehavior::switchStatus( ) {
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
	if ( range <= _attack_range && _before_state != ENEMY_STATE_ATTACK  ) {
		_enemy_state = ENEMY_STATE_ATTACK;
	}
		//UŒ‚’†
	if ( _animation->getMotion( ) == Animation::MOTION_GHOST_ATTACK && !_animation->isEndAnimation( ) ) {
		_enemy_state = ENEMY_STATE_ATTACK;
		//ƒ_ƒ[ƒW
		if ( _animation->getAnimTime( ) == ATTACK_TIME ) {
			onAttack( );
		}
	}
	if ( _before_hp > _parent->getStatus( ).hp ) {
		_on_damage = true;
		Effect effect;
		int damage_effect = effect.setEffect( Effect::EFFECT_DAMAGE );
		effect.drawEffect( damage_effect, Vector( DAMAGE_SCALE, DAMAGE_SCALE, DAMAGE_SCALE ), _parent->getPos( ), _parent->getDir( ) );
	}
	if ( _parent->getStatus( ).hp <= 0 ) {
		_enemy_state = ENEMY_STATE_DEAD;
	}
}

void EnemyGhostBehavior::animationUpdate( ) {
	if ( _animation->getMotion( ) == Animation::MOTION_GHOST_DEAD ) {
		if ( _animation->isEndAnimation( ) ) {
			_parent->dead( );
		}
		return;
	}
	if ( _animation->getMotion( ) == Animation::MOTION_GHOST_DAMAGE && !_animation->isEndAnimation( ) ) {
		_enemy_state = ENEMY_STATE_WAIT;
		return;
	}

	if ( _enemy_state == ENEMY_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GHOST_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GHOST_WAIT, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _enemy_state == ENEMY_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GHOST_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GHOST_WALK, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _enemy_state == ENEMY_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GHOST_ATTACK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GHOST_ATTACK, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _on_damage ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GHOST_DAMAGE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GHOST_DAMAGE, MOTION_SPEED ) );
		}
	}
	if ( _enemy_state == ENEMY_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_GHOST_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_GHOST_DEAD, MOTION_SPEED ) );
		}
	}
}

void EnemyGhostBehavior::onAttack( ) {
	Vector dir = _parent->getDir( );
	Vector pos = _parent->getPos( );

	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	int power = _parent->getStatus( ).power;
	BulletFireBallPtr bullet = BulletFireBallPtr ( new BulletFireBall( pos + Vector( 0, 0, 0.5 ), dir, power ) );
	weapon->add( bullet );
}