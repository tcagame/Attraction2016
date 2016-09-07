#include "BulletBeam.h"

const int BEAM_POWER = 100;

const double SPEED = 0.05;
const double RADIUS = 0.3;
const double LENGTH = 6.0;
const int PARTICLE = 8;

BulletBeam::BulletBeam( const Vector& pos, const Vector& dir ) 
: Bullet( Bullet::TYPE_BEAM ) {
	_pos = pos;
	_dir = dir.normalize( );
	_expired = true;
	_radius = RADIUS;
	_power = BEAM_POWER;
	_length = 0;

	while ( _length < LENGTH ) {
		double length = _length + 1.0;
		Vector p = pos + _dir * length;
		attackEnemy( p, _power );
		_length = length;
		Vector vec( 0, 0, _radius );
		Matrix mat = Matrix::makeTransformRotation( _dir, PI2 / PARTICLE );
		for ( int i =0; i < PARTICLE; i++ ) {
			vec = mat.multiply( vec );
			Vector lay_pos = p + vec;
			attackEnemy( lay_pos, _power );
		}
	}
}

BulletBeam::~BulletBeam( ) {
}


bool BulletBeam::update( ) {
	if ( _show ) {
		_show = false;
		return true;
	}
	return false;
}