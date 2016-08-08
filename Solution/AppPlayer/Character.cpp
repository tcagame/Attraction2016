#include "Character.h"
#include "Behavior.h"

Character::Character( TYPE type, BehaviorPtr behavior ) :
CHARACTER_TYPE( type ) {
	_behavior = behavior;
	init( );
}

Character::~Character( ) {
}

void Character::update( ) {
	if ( _expired ) {
		_behavior->update( );
	}
}

void Character::move( Vector vec ) {
	_pos += vec;
}

void Character::create( Vector pos ) {
	_pos = pos;
	_expired = true;
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

void Character::setPos( Vector pos ) {
	_pos = pos;
}

void Character::setDir( Vector dir ) {
	_dir = dir;
}

void Character::setStatus( Character::STATUS status ) {
	_status = status;
}

void Character::setExpired( bool expired ) {
	_expired = expired;
}