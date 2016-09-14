#include "Character.h"
#include "Player.h"
#include "Behavior.h"
#include "App.h"
#include "Sound.h"
#include "Field.h"
#include "GroundModel.h"
#include "Cohort.h"
#include "Enemy.h"
#include "PlayerBehavior.h"
#include "Adventure.h"
#include "Camera.h"

const Vector START_DIR = Vector( 0, 1, 0 );
const int SE_TIME = 15;

Character::Character( TYPE type, BehaviorPtr behavior, Character::STATUS status, std::string character_name ) :
CHARACTER_TYPE( type ),
_origin_status( status ) {
	_behavior = behavior;
	_status = status;
	_character_name = character_name;
	_expired = false;
	_max_hp = status.hp;
}

Character::~Character( ) {
	
}

void Character::update( ) {
	CameraPtr camera = Camera::getTask( );
	if ( !camera->isInScreen( getPos( ) ) ) {
		return;
	}
	if ( _expired ) {
		_behavior->mainLoop( );
	}
}


void Character::reset( ){
	_status = _origin_status;
	_behavior->reset( );
	_expired = false;
	AppPtr app = App::getTask( );
	FieldPtr field = app->getField( );
	field->delTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
}

bool Character::move( const Vector& vec ) {
	if ( vec.getLength( ) > 0 ) {
		_dir = vec.normalize( );
	}
	AppPtr app = App::getTask( );
	FieldPtr field = app->getField( );
	
	field->delTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );

	Vector store = _pos;
	Vector move_pos = _pos + vec;
	ObjectPtr object = field->getTarget( ( int )move_pos.x, ( int )move_pos.y );
	if ( !object ) {
		GroundModelPtr ground_model = app->getGroundModel( );
		bool is_ground = ground_model->isCollisionGround( move_pos );//’n–Ê‚Æ‚Ì”»’è
		if ( is_ground ) {
			_pos = move_pos;
		}
	}

	field->setTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );

	return
		( int )_pos.x == ( int )store.x &&
		( int )_pos.y == ( int )store.y;   
}

void Character::create( const Vector& pos ) {
	_pos = pos;
	_dir = START_DIR;
	_expired = true;
	AppPtr App = App::getTask( );
	FieldPtr field = App->getField( );
	field->setTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
}

void Character::damage( unsigned int power ) {
	bool isPlayer = CHARACTER_TYPE == TYPE_PLAYER;
	PlayerBehaviorPtr player_behavior;
	if ( isPlayer ) {
		player_behavior  = std::dynamic_pointer_cast< PlayerBehavior >( _behavior );
	}
	bool is_unrivaled  = isPlayer && player_behavior->isDeathblow( );
	if ( !is_unrivaled ) {
		_status.hp -= power;
		if ( _status.hp < 0 ) {
			_status.hp = 0;
		}
	}
	SoundPtr sound = Sound::getTask( );
	sound->playSE( Sound::SE_PLAYER_DAMAGE );
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
	if ( !_expired ) {
		return;
	}
	AppPtr app = App::getTask();
	FieldPtr field = app->getField();
	field->delTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
	_expired = false;
	if ( CHARACTER_TYPE != TYPE_PLAYER ) {
		return;
	}
	//AdventurePtr adventure = app->getAdventure( );
	if ( app->getPlayerId( ) >= PLAYER_ETUDE_RED ) {
		//adventure->set( Adventure::TYPE_COMMON_MINOTAUR_DEAD );
		//adventure->set( Adventure::TYPE_COMMON_AFTER_MINOTAUR_DEAD );
	}
	SoundPtr sound = Sound::getTask( );
	sound->playSE( Sound::SE_PLAYER_DEAD );
}