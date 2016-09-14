#include "BulletBulletRain.h"
#include "App.h"
#include "Effect.h"

const int VANISH_TIME = 50;
const int WAIT_TIME = 60;
const double BULLET_SCALE = 0.5;
const double RANGE = 3;
const double RADIUS = 5;
const int PARTICLE = 12;
const int POWER = 50;
const int SPEED = 1;

BulletBulletRain::BulletBulletRain( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_BULLET_RAIN ) {
	_pos = pos + Vector( 0, 0, 0.5 ) + dir * RANGE;
	_dir = dir.normalize( );
	_power = POWER * power;
	_speed = SPEED;
	_exist_time = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_BULLET_RAIN );
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), pos, dir );
}

BulletBulletRain::~BulletBulletRain( ) {
}

bool BulletBulletRain::update( ) {
	_exist_time++;
	if ( _exist_time < WAIT_TIME  ) {
		return true;
	}
	if ( _exist_time >= WAIT_TIME + VANISH_TIME  ) {
		return false;
	}
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), PI2 / PARTICLE );
	Vector radius_dir = Vector( 0, 1, 0 );
	attackEnemy( _pos, POWER );
	for ( int i = 0; i < PARTICLE; i++ ) {
		radius_dir = mat.multiply( radius_dir );
		for ( int j = 1; j < RADIUS + 1; j++ ) {
			Vector pos = _pos + radius_dir * j;
			attackEnemy( pos, _power );
		}
	}
	return true;
}