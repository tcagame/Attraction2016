#include "BulletLay.h"
#include "Effect.h"

const int LAY_POWER = 100;

const double SPEED = 0.05;
const double RADIUS = 0.3 * Bullet::BULLET_SCALE;
const double LENGTH = 25.0 * Bullet::BULLET_SCALE;
const int PARTICLE = 8;
const Vector EFFECT_DIFF_POS = Vector( 0, 0, -2 );
const double EFFECT_SCALE = 1.5 * Bullet::BULLET_SCALE;

BulletLay::BulletLay( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_LAY ) {
	_power = LAY_POWER * power;
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
	Vector effect_pos = pos - dir * 2.4 + EFFECT_DIFF_POS;
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), effect_pos, dir );
}

BulletLay::~BulletLay( ) {
}

double BulletLay::getLength( ) const {
	return _length;
}

double BulletLay::getRadius( ) const {
	return _radius;
}

bool BulletLay::update( ) {
	if ( _show ) {
		_show = false;
		return true;
	}

	return false;
}
