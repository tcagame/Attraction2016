#include "BulletSmash.h"
#include "App.h"
#include "Effect.h"

const int WAIT_TIME = 10;
const double EFFECT_SCALE = 0.1;
const double RANGE = 0.5;
const double RADIUS = 1;
const int PARTICLE = 12;
const int POWER = 50;
const int SPEED = 1;

BulletSmash::BulletSmash( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_CLEAVE ) {
	_pos = pos + Vector( 0, 0, 0.5 ) + dir * RANGE;
	_dir = dir.normalize( );
	_power = POWER * power;
	_speed = SPEED;
	_exist_time = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_ENEMY_ATTACK_SMASH );
	Vector effect_pos = pos + Vector( 0,0,0.5 );
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), effect_pos, dir );
}

BulletSmash::~BulletSmash( ) {
}

bool BulletSmash::update( ) {
	_exist_time++;
	if ( _exist_time < WAIT_TIME  ) {
		return true;
	}
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), PI2 / PARTICLE );
	Vector radius_dir = Vector( 0, 1, 0 );
	attackEnemy( _pos, _power );
	for ( int i = 0; i < PARTICLE; i++ ) {
		radius_dir = mat.multiply( radius_dir );
		for ( int j = 1; j < RADIUS + 1; j++ ) {
			Vector pos = _pos + radius_dir * j;
			attackPlayer( pos, _power );
		}
	}
	return false;
}