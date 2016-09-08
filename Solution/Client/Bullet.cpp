#include "Bullet.h"
#include "App.h"
#include "Cohort.h"
#include "Enemy.h"
#include "mathmatics.h"
#include "Player.h"
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
	/*AppPtr app = App::getTask( );
	CohortPtr cohort = app->getCohort( );
	for( int i = 0; i < cohort->getMaxNum( ); i++ ) {
		EnemyPtr enemy = cohort->getEnemy( i );
		if ( !enemy->isExpired( ) ) {
			continue;
		}
		enemyReceiveDamage( enemy, pos, power );
	}
	EnemyPtr enemy = cohort->getBoss( );
	enemyReceiveDamage( enemy, pos, power );*/
}

void Bullet::enemyReceiveDamage( EnemyPtr enemy, const Vector& pos, int power ) {
	AppPtr app = App::getTask( );
	double bottom = enemy->getPos( ).z;
	double top = bottom + 2;
	if ( pos.z > bottom && pos.z < top ) {
		Vector distance = pos - enemy->getPos( );
		double length = distance.getLength( );
		Character::STATUS status = enemy->getStatus( );
		if ( length <= 1 && status.hp > 0 ) {
			enemy->damage( power );
			status  = enemy->getStatus( );
			if ( status.hp <= 0 ) {
				PlayerPtr player = app->getPlayer( );
				player->addSP( 10 );
			}
		}
	}
}