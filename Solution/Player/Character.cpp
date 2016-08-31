#include "Character.h"
#include "Behavior.h"
#include "App.h"
#include "GroundModel.h"

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
	Vector move_pos = getPos( ) + vec;
	bool is_ground = ground_model->isCollisionGround( move_pos );//’n–Ê‚Æ‚Ì”»’è
	if ( is_ground ) {
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