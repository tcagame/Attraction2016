#include "EnemyArmorBehavior.h"
#include "Character.h"
#include "Animation.h"
#include "Effect.h"
#include "App.h"
#include "Sound.h"
#include "Player.h"

const double MOTION_SPEED = 1;
const double ATTACK_TIME = 40.0;
const double DAMAGE_SCALE = 0.5;

EnemyArmorBehavior::EnemyArmorBehavior( ) {
	_attack_range = 2.0;
	_move_range = 10.5;
	_on_damage = false;

	_befor_hp = -1;
}


EnemyArmorBehavior::~EnemyArmorBehavior( ) {
}


void EnemyArmorBehavior::update( ) {
	searchTarget( );
	movePosToTarget( );
	switchStatus( );
	_before_state = _enemy_state;
	_befor_hp = _parent->getStatus( ).hp;
}

void EnemyArmorBehavior::searchTarget( ) {
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

void EnemyArmorBehavior::movePosToTarget( ) {
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

void EnemyArmorBehavior::switchStatus( ) {
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
	if ( _animation->getMotion( ) == Animation::MOTION_ARMOR_ATTACK && !_animation->isEndAnimation( ) ) {
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

void EnemyArmorBehavior::animationUpdate( ) {
	if ( _animation->getMotion( ) == Animation::MOTION_ARMOR_DEAD ) {
		if ( _animation->isEndAnimation( ) ) {
			_parent->dead( );
		}
		return;
	}
	if ( _animation->getMotion( ) == Animation::MOTION_ARMOR_DAMAGE && !_animation->isEndAnimation( ) ) {
		_enemy_state = ENEMY_STATE_WAIT;
		return;
	}
	if ( _enemy_state == ENEMY_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_ARMOR_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_ARMOR_WAIT, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _enemy_state == ENEMY_STATE_WALK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_ARMOR_WALK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_ARMOR_WALK, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _enemy_state == ENEMY_STATE_ATTACK ) {
		if ( _animation->getMotion( ) != Animation::MOTION_ARMOR_ATTACK ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_ARMOR_ATTACK, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
			if ( _animation->getAnimTime( ) == 50.0 ) {
				onAttack( );
			}
		}
	}
	if ( _on_damage ) {
		if ( _animation->getMotion( ) != Animation::MOTION_ARMOR_DAMAGE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_ARMOR_DAMAGE, MOTION_SPEED ) );
		}
	}
	if ( _enemy_state == ENEMY_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_ARMOR_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_ARMOR_DEAD, MOTION_SPEED ) );
		}
	}
}


void EnemyArmorBehavior::onAttack( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayerMine( );
	if ( !player ) {
		return;
	}
	Vector player_pos = player->getPos( );
	Vector vec = player_pos - _parent->getPos( );
	Vector dir = vec.normalize( );
	Vector attack_pos = _parent->getPos( ) +  dir * 1.0;
	Vector smash_dis = attack_pos - player_pos;

	if ( player && smash_dis.getLength( ) < 2.0 ) {
		player->damage( _parent->getStatus( ).power );
	}
}