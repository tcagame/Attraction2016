#include "Character.h"
#include "Behavior.h"
#include "App.h"
#include "GroundModel.h"
#include "Cohort.h"
#include "Enemy.h"

Vector START_DIR = Vector( 0, 1, 0 );

Character::Character( TYPE type, BehaviorPtr behavior ) :
CHARACTER_TYPE( type ) {
	_behavior = behavior;
}

Character::~Character( ) {
}

void Character::update( ) {
	if ( _expired ) {
		_behavior->mainLoop( );
	}
}

void Character::move( Vector vec ) {
	AppPtr app = App::getTask( );
	GroundModelPtr ground_model = app->getGroundModel( );
	CohortPtr cohort = app->getCohort( );
	Vector move_pos = getPos( ) + vec;

	bool is_character = false;
	int max_enemy = cohort->getMaxNum( );
	for ( int i = 0; i < max_enemy; i++ ) {
		EnemyPtr enemy = cohort->getEnemy( i );
		if ( !enemy->isExpired( ) ) {
			continue;
		}
		Vector enemy_pos = enemy->getPos( );
		STATUS status = enemy->getStatus( );
		double length = ( move_pos - enemy_pos ).getLength( );
		if ( length < status.width ) {
			is_character = true;
			break;
		}
	}
	bool is_ground = ground_model->isCollisionGround( move_pos );//’n–Ê‚Æ‚Ì”»’è
	if ( is_ground && !is_character ) {
		_pos += vec;
	}
	if ( vec.getLength( ) > 0 ) {
		_dir = vec.normalize( );
	}
}

void Character::create( Vector pos, Character::STATUS status ) {
	_status = status;
	_pos = pos;
	_dir = START_DIR;
	_expired = true;
	_behavior->init( );
}

void Character::damage( unsigned int power ) {
	_status.hp -= power;
	if ( _status.hp <= 594900 ) {
		int i = 0;
	}
}

Vector Character::getPos( ) const {
	return _pos;
}

Vector Character::getDir( ) const {
	return _dir;
}

Character::STATUS Character::getStatus( ) const {
	return _status;
}

AnimationPtr Character::getAnimation( ) {
	return _behavior->getAnimation( );
}

Character::TYPE Character::getType( ) const {
	return CHARACTER_TYPE;
}

bool Character::isExpired( ) const {
	return _expired;
}

void Character::dead( ) {
	_expired = false;
}