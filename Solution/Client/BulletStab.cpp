#include "BulletStab.h"

const int SWORD_POWER = 25;
const int SWORD_LENGTH = 5;
const int SWORD_RATIO = 5;
const double SWORD_SPEED = 0.5;
const double WAIT_TIME = 1.0;

BulletStab::BulletStab( const Vector& pos, double dir_x, double dir_y ) 
: Bullet( Bullet::TYPE_STAB ) {
	_pos = pos;
	_dir = Vector( dir_x, dir_y ).normalize( );
	_ratio = 0;
	_hit_pos = pos;
}

BulletStab::~BulletStab() {
}

double BulletStab::getLength( ) const {
	return SWORD_LENGTH;
}

bool BulletStab::update( ) {
	_ratio += SWORD_SPEED;
	if ( _ratio < WAIT_TIME ) {
		true;
	}
	for ( int i  = 0; i < SWORD_RATIO; i++ ) {
		Vector pos = getPos( );
		double length = getLength( ) * i / SWORD_RATIO;
		Vector p = pos + _dir.normalize( ) * length;
		p = p + Vector( 0, 0, 0.5 );
		attackEnemy( p, SWORD_POWER );
		_hit_pos = p;
	}
	return false;
}