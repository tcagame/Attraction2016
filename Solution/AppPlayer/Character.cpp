#include "Character.h"
#include "Behavior.h"

Vector START_DIR = Vector( 0, 1, 0 );

Character::Character( TYPE type, BehaviorPtr behavior ) :
CHARACTER_TYPE( type ) {
	_behavior = behavior;
	_behavior->setParent( CharacterPtr( this ) );
}

Character::~Character( ) {
}

void Character::update( ) {
	if ( _expired ) {
		_behavior->mainLoop( );
	}
}

void Character::move( Vector vec ) {
	_pos += vec;
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