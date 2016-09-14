#include "BulletDash.h"
#include "Effect.h"

const int POWER = 10;
const int ANIMATION_TIME = 5;
const int WAIT_TIME = 8;
const double RANGE = 1;

BulletDash::BulletDash( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_DASH )
, _count( 0 ) {
	_pos = pos + Vector( 0, 0, 0.5 );
	_dir = dir;
}

BulletDash::~BulletDash( ) {
}

double BulletDash::getLength( ) const {
	return RANGE * ( _count - WAIT_TIME ) / ANIMATION_TIME;
}

bool BulletDash::update( ) {
	_count++;
	if ( _count < WAIT_TIME ) {
		return true;
	}
	if ( _count >= WAIT_TIME + ANIMATION_TIME ) {
		return false;
	}

	double range = getLength( );
	Vector pos = getPos( ) + _dir * range;
	attackPlayer( pos, POWER );

	return true;
}
