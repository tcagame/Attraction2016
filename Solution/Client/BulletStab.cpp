#include "BulletStab.h"

const int SWORD_POWER = 25;
const int SWORD_LENGTH = 3;
const int STAB_RATIO = 4;
const double SWORD_SPEED = SWORD_LENGTH / STAB_RATIO;

BulletStab::BulletStab( const Vector& pos, double dir_x, double dir_y ) 
: Bullet( Bullet::TYPE_STAB )
, _pos( pos )
,_dir( dir_x, dir_y ){
	_ratio = 0;
}

BulletStab::~BulletStab() {
}


Vector BulletStab::getPos( ) const {
	return _pos;
}

double BulletStab::getLength( ) const {
	return SWORD_LENGTH;
}

bool BulletStab::update( ) {
	_ratio += SWORD_SPEED;
	if ( _ratio < 1.0 ) {
		return true;
	}

	Vector pos = getPos( );
	double length = getLength( ) * _ratio;
	Vector p = pos + _dir.normalize( ) * length;
	attackEnemy( p, SWORD_POWER );
	return false;
}