#include "Bullet.h"
#include "App.h"
#include "Cohort.h"
#include "Enemy.h"
#include "mathmatics.h"
#include "Player.h"
#include "Field.h"
#include "Framework.h"

const double Bullet::BULLET_SCALE( 1.0 );//ƒ‚ƒfƒ‹‚Ì‘å‚«‚³‚É‡‚í‚¹‚éB

Bullet::Bullet( TYPE type )
: _type( type ) {
}

Bullet::~Bullet( ) {
}

Bullet::TYPE Bullet::getType( ) const {
	return _type;
}

Vector Bullet::getPos( ) const {
	return _pos;
}

Vector Bullet::getDir( ) const {
	return _dir;
}

void Bullet::attackEnemy( const Vector& pos, int power ) {
	AppPtr app = App::getTask( );
	FieldPtr field = app->getField( );
	ObjectPtr object = field->getTarget( ( int )pos.x, ( int )pos.y );
	EnemyPtr enemy = std::dynamic_pointer_cast< Enemy >( object );
	if ( !enemy ) {
		return;
	}
	Character::STATUS status = enemy->getStatus();
	enemy->damage( power );

	PlayerPtr player = app->getPlayerMine( );
	if ( player && !isDeathBlow( ) ) {
		player->addSP( 100 );
	}
}

void Bullet::attackPlayer( const Vector& pos, int power ) {
	AppPtr app = App::getTask( );
	FieldPtr field = app->getField( );
	ObjectPtr object = field->getTarget( ( int )pos.x, ( int )pos.y );
	PlayerPtr player = std::dynamic_pointer_cast< Player >( object );
	if ( !player ) {
		return;
	}
	if ( player->getCharacterName( ) == "PLAYER_ETUDE" ) {
		return;
	}

	player->damage( power );
}

bool Bullet::isDeathBlow( ) {
	bool result = false;
	if ( _type == TYPE_EXCALIBUR ) {
		result = true;
	}
	if ( _type == TYPE_SPLASH ) {
		result = true;
	}
	if ( _type == TYPE_RUSH ) {
		result = true;
	}
	if ( _type == TYPE_BULLET_RAIN ) {
		result = true;
	}
	return result;
}