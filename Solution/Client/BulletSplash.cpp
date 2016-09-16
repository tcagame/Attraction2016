#include "BulletSplash.h"
#include "Effect.h"

const int POWER = 500;

const double RADIUS = 5.0 * Bullet::BULLET_SCALE;
const double LENGTH = 20.0 * Bullet::BULLET_SCALE;
const int PARTICLE = ( int )( 12 * Bullet::BULLET_SCALE );
const double WAIT_TIME = 50.0;
const double END_TIME = 30.0 + WAIT_TIME;
const Vector EFFECT_DIFF_POS = Vector( 0, 0, -0.4 );
const double EFFECT_SCALE = 0.5 * Bullet::BULLET_SCALE;

BulletSplash::BulletSplash( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_SPLASH ) {
	_pos = pos;
	_dir = dir.normalize( );
	_expired = true;
	_radius = RADIUS;
	_power = POWER * power;
	_length = 0;
	_time = 0;

	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_SPLASH );
	Vector effect_pos = pos + EFFECT_DIFF_POS;
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), effect_pos, dir );
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
		double length = _length;
		Vector p = _pos + _dir * length;
		attackEnemy( p, _power );
		Vector vec( 0, 0, _radius );
		Matrix mat = Matrix::makeTransformRotation( _dir, PI2 / PARTICLE );
		for ( int i = 0; i < PARTICLE; i++ ) {
			vec = mat.multiply( vec );
			for ( int j = 0; j < RADIUS; j++ ) {
				Vector lay_pos = p + vec.normalize( ) * j;
				attackEnemy( lay_pos, _power );
			}
		}
		_length += 1.0;
	}
	_length = 0;
	if ( _time > END_TIME ) {
		return false;
	}
	return true;
}
