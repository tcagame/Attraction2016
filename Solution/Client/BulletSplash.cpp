#include "BulletSplash.h"
#include "Effect.h"

const int POWER = 100;

const double SPEED = 0.05;
const double RADIUS = 1.0;
const double LENGTH = 10.0;
const int PARTICLE = 8;
const double WAIT_TIME = 10.0;
const double END_TIME = 40.0;

BulletSplash::BulletSplash( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_SPLASH ) {
	_pos = pos;
	_dir = dir.normalize( );
	_expired = true;
	_radius = RADIUS;
	_power = POWER;
	_length = 0;
	_time = 0;

	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_SPLASH );
	effect.drawEffect( _effect_handle, Vector( 1, 1, 1 ), pos, dir );
}

BulletSplash::~BulletSplash( ) {
}

double BulletSplash::getLength( ) const {
	return _length;
}

double BulletSplash::getRadius( ) const {
	return _radius;
}

bool BulletSplash::update( ) {
	_time++;
	if ( _time < WAIT_TIME ) {
		return true;
	}
	while ( _length < LENGTH ) {
		double length = _length + 1.0;
		Vector p = _pos + _dir * length;
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
	if ( _time < END_TIME ) {
		return false;
	}
	return true;
}
