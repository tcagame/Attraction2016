#include "BulletDash.h"
#include "Effect.h"

const int POWER = 10;
const int ANIMATION_TIME = 7;
const double SPEED = 0.5;

BulletDash::BulletDash( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_DASH )
, _count( 0 ) {
	_power = POWER * power;
	_pos = pos + Vector( 0, 0, 0.5 );
	_dir = dir;
}

BulletDash::~BulletDash( ) {
}

double BulletDash::getLength( ) const {
	return SPEED;
}

bool BulletDash::update( ) {
	_count++;
	if ( _count >= ANIMATION_TIME ) {
		return false;
	}
	double speed = getLength( );
	_pos += _dir * speed;
	attackPlayer( _pos, _power );

	return true;
}
