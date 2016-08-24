#include "Bullet.h"
#include "App.h"
#include "Cohort.h"
#include "Enemy.h"
#include "mathmatics.h"
#include "Framework.h"

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


void Bullet::attackEnemy( const Vector& pos, int power ) {
	AppPtr app = App::getTask( );
	CohortPtr cohort = app->getCohort( );
	for( int i = 0; i < cohort->getMaxNum( ); i++ ) {
		EnemyPtr enemy = cohort->getEnemy( i );
		double bottom = enemy->getPos( ).z;
		double top = bottom + 2;
		if ( pos.z > bottom && pos.z < top ) {
			Vector distance = pos - enemy->getPos( );
			double length = distance.getLength( );
			if ( length <= 1 ) {
				enemy->damage( power );
			}
		}
	}
}