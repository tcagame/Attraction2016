#include "BulletJab.h"
#include "Effect.h"

const int POWER = 50;
const int ANIMATION_TIME = 8;
const int WAIT_TIME = 8;
const double RANGE = 1.5 * Bullet::BULLET_SCALE;
const double EFFECT_SCALE = 0.5 * BulletJab::BULLET_SCALE;

BulletJab::BulletJab( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_JAB )
, _count( 0 ) {
	_power = POWER * power;
	_pos = pos;
	_dir = dir;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_JAB );
	Vector effect_pos = pos + dir * Bullet::BULLET_SCALE + Vector( 0 ,0, 0.3 ) * Bullet::BULLET_SCALE;
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), effect_pos, dir );
}

BulletJab::~BulletJab( ) {
}

double BulletJab::getLength( ) const {
	return RANGE * ( _count - WAIT_TIME ) / ANIMATION_TIME;
}

bool BulletJab::update( ) {
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
