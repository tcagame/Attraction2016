#include "BulletStab.h"

const int SWORD_POWER = 25;
const int SWORD_LENGTH = 5;
const double SWORD_SPEED = 0.5;

BulletStab::BulletStab( const Vector& pos, double dir_x, double dir_y ) 
: Bullet( Bullet::TYPE_STAB )
, _pos( pos )
,_dir( dir_x, dir_y ){
	_ratio = 0;
	_hit_pos = pos;
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
	Vector pos = getPos( );
	double length = getLength( ) * _ratio;
	Vector p = pos + _dir.normalize( ) * length;
	p = p + Vector( 0, 0, 0.5 );
	attackEnemy( p, SWORD_POWER );
	_hit_pos = p;
	if ( length < SWORD_LENGTH ) {
		return true;
	}
	return false;
}