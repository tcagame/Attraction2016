#include "BulletImpact.h"
#include "Framework.h"

const int IMPACT_POWER = 100;
const int TIME = 3;
const double RANGE = 5;

void BulletImpact::initialize( ) {
}

BulletImpact::BulletImpact( const Vector& pos, const Vector& dir )
: Bullet( Bullet::IMPACT )
, _pos( pos )
, _dir( dir )
, _count( 0 ) {
	_pos += Vector( 0, 0, 0.5 );
}

Vector BulletImpact::getPos( ) const {
	return _pos;
}

double BulletImpact::getLength( ) const {
	return _count* RANGE / TIME;
}

BulletImpact::~BulletImpact( ) {
}

bool BulletImpact::update( ) {
	_count++;
	if ( _count >= TIME ) {
		return false;
	}

	int range = ( int )getLength( );
	Vector pos = getPos( ) + _dir * range;
	attackEnemy( pos, IMPACT_POWER );
	return true;
}
