#include "Character.h"
#include "Behavior.h"
#include "App.h"
#include "Field.h"
#include "GroundModel.h"
#include "Cohort.h"
#include "Enemy.h"

Vector START_DIR = Vector( 0, 1, 0 );

Character::Character( TYPE type, BehaviorPtr behavior, Character::STATUS status, std::string character_name ) :
CHARACTER_TYPE( type ) {
	_behavior = behavior;
	_status = status;
	_origin_status = _status;
	_character_name = character_name;
	_expired = false;
	_max_hp = status.hp;
	
}

Character::~Character( ) {
}

void Character::update( ) {
	if ( _expired ) {
		_behavior->mainLoop( );
	}
}

void Character::reset( ){
	_status = _origin_status;
	_expired = false;
	AppPtr app = App::getTask();
	FieldPtr field = app->getField();
	field->delTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
}

void Character::move( const Vector& vec ) {

	if ( vec.getLength( ) > 0 ) {
		_dir = vec.normalize( );
	}
	AppPtr app = App::getTask( );
	FieldPtr field = app->getField( );
	Vector move_pos = getPos( ) + vec;
	field->delTarget( ( int )move_pos.x, ( int )move_pos.y, getThis( ) );
	bool is_character = !field->setTarget( ( int )move_pos.x, ( int )move_pos.y, getThis( ) );
	if ( is_character ) {
		field->setTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
		return;
	}
	
	GroundModelPtr ground_model = app->getGroundModel( );
	bool is_ground = ground_model->isCollisionGround( move_pos );//’n–Ê‚Æ‚Ì”»’è
	if ( is_ground ) {
		field->delTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
		_pos += vec;
		field->setTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
	}
}

void Character::create( const Vector& pos ) {
	_pos = pos;
	_dir = START_DIR;
	_expired = true;
	AppPtr App = App::getTask( );
	FieldPtr field = App->getField( );
	field->setTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
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

int Character::getMaxHp( ) const {
	return _max_hp;
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
	AppPtr app = App::getTask();
	FieldPtr field = app->getField();
	field->delTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
	_expired = false;
}