#include "BulletImpact.h"
#include "Effect.h"

const int POWER = 100;
const int WAIT_TIME = 8;
const int ANIMATION_TIME = 10;
const double RANGE = 3 * Bullet::BULLET_SCALE;
const double EFFECT_SCALE = 0.5 * Bullet::BULLET_SCALE;

BulletImpact::BulletImpact( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_IMPACT )
, _count( 0 ) {
	_power = POWER * power;
	_pos = pos;
	_dir = dir;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_IMPACT );
	Vector effect_pos = pos + Vector( 0, 0, -0.2 ) * Bullet::BULLET_SCALE + _dir * 0.5 * Bullet::BULLET_SCALE;
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), effect_pos, dir );
}

BulletImpact::~BulletImpact( ) {
}

double BulletImpact::getLength( ) const {
	return RANGE * ( _count - WAIT_TIME ) / ANIMATION_TIME;
}

bool BulletImpact::update( ) {
	_count++;
	if ( _count < WAIT_TIME ) {
		return true;
	}
	if ( _count >= WAIT_TIME + ANIMATION_TIME ) {
		return false;
	}

	double range = getLength( );
	Vector pos = getPos( ) + _dir * range;
	attackEnemy( pos, _power );
	return true;
}
