#include "BulletBeam.h"
#include "Effect.h"


const int BEAM_POWER = 100;
const double SPEED = 0.05;
const double RADIUS = 1.0 * Bullet::BULLET_SCALE;
const double LENGTH = 15.0 * Bullet::BULLET_SCALE;
const double EFFECT_SCALE = Bullet::BULLET_SCALE;
const int PARTICLE = 8;

BulletBeam::BulletBeam( const Vector& pos, const Vector& dir, int power ) 
: Bullet( Bullet::TYPE_BEAM ) {
	_pos = pos;
	_dir = dir.normalize( );
	_expired = true;
	_radius = RADIUS;
	_power = BEAM_POWER * power;
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
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_BEAM );
	Vector effect_pos = _pos;
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), effect_pos, dir );
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