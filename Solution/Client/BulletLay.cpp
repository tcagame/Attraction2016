#include "BulletLay.h"
#include "Effect.h"

const int LAY_POWER = 100;

const double SPEED = 0.05;
const double RADIUS = 0.1;
const double LENGTH = 10.0;
const int PARTICLE = 8;

BulletLay::BulletLay( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_LAY ) {
	_pos = pos;
	_dir = dir.normalize( );
	_expired = true;
	_radius = RADIUS;
	_power = LAY_POWER;
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
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_LAY );
	effect.drawEffect( _effect_handle, Vector( 1, 1, 1 ), pos, dir );
}

double BulletLay::getLength( ) const {
	return _length;
}

double BulletLay::getRadius( ) const {
	return _radius;
}

BulletLay::~BulletLay( ) {
}

bool BulletLay::update( ) {
	if ( _show ) {
		_show = false;
		return true;
	}

	return false;
}
