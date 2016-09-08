#include "Bullet.h"
#include "App.h"
#include "Cohort.h"
#include "Enemy.h"
#include "mathmatics.h"
#include "Player.h"
#include "Field.h"
#include "Framework.h"

Bullet::Bullet( TYPE type )
: _type( type ) {
	_hit_pos = Vector( 0, 0, 0 );
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

Vector Bullet::getHitPos( ) const {
	return _hit_pos;
}

void Bullet::attackEnemy( const Vector& pos, int power ) {
	//‚ ‚½‚è”»’è’²®’†
	AppPtr app = App::getTask( );
	FieldPtr field = app->getField( );
	ObjectPtr object = field->getTarget( ( int )pos.x, ( int )pos.y );
	EnemyPtr enemy = std::dynamic_pointer_cast< Enemy >(object);
	if ( !enemy ) {
		return;
	}
	double bottom = enemy->getPos().z;
	double top = bottom + 2;
	if ( pos.z > bottom && pos.z < top ) {
		Character::STATUS status = enemy->getStatus();
		if ( status.hp > 0 ) {
			enemy->damage( power );
			status = enemy->getStatus( );
			if ( status.hp <= 0 ) {
				PlayerPtr player = app->getPlayer( );
				player->addSP( 10 );
			}
		}
	}
}