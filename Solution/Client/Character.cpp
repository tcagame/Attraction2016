#include "Character.h"
#include "Behavior.h"
#include "App.h"
#include "GroundModel.h"
#include "Cohort.h"
#include "Enemy.h"

Vector START_DIR = Vector( 0, 1, 0 );

Character::Character( TYPE type, BehaviorPtr behavior, Character::STATUS status, std::string character_name ) :
CHARACTER_TYPE( type ) {
	_behavior = behavior;
	_status = status;
	_character_name = character_name;
	_expired = false;
}

Character::~Character( ) {
}

void Character::update( ) {
	if ( _expired ) {
		_behavior->mainLoop( );
	}
}

void Character::move( const Vector& vec ) {
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
		//Ž©g‚Æ‚Í”»’è‚µ‚È‚¢
		if ( enemy.get( ) == this ) {
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

void Character::create( const Vector& pos ) {
	_pos = pos;
	_dir = START_DIR;
	_expired = true;
	_behavior->init( );
}

void Character::damage( unsigned int power ) {
	_status.hp -= power;
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

AnimationPtr Character::getAnimation( ) const {
	return _behavior->getAnimation( );
}

Character::TYPE Character::getType( ) const {
	return CHARACTER_TYPE;
}

std::string Character::getCharacterName( ) const {
	return _character_name;
}

bool Character::isExpired( ) const {
	return _expired;
}

void Character::dead( ) {
	_expired = false;
}