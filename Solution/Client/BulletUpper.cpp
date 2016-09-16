#include "BulletUpper.h"
#include "Effect.h"

const int POWER = 50;
const int WAIT_TIME = 15;
const double RANGE = 3 * Bullet::BULLET_SCALE;
const int PARTICLE = 8;
const double EFFECT_SCALE = 0.5 * Bullet::BULLET_SCALE;

BulletUpper::BulletUpper( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_UPPER )
, _count( 0 ) {
	_pos = pos;
	_dir = dir;
	_power = POWER * power;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_UPPER );
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), -PI / 2 );
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), pos + dir * Bullet::BULLET_SCALE + Vector( 0, 0, -0.2 ), mat.multiply( dir ) );
}

BulletUpper::~BulletUpper( ) {
}

bool BulletUpper::update( ) {
	_count++;
	if ( _count < WAIT_TIME ) {
		return true;
	}

	for ( int i = 0; i< PARTICLE; i++ ) {
		double range = RANGE * i / PARTICLE;
		Vector pos = getPos( ) + _dir * range;
		attackEnemy( pos, _power );
	}
	return false;
}