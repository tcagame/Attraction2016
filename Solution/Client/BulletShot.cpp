#include "BulletShot.h"
#include "Cohort.h"
#include "Enemy.h"
#include "App.h"
#include "Effect.h"

const int VANISH_TIME = 50;
const int WAIT_TIME = 40;
const double EFFECT_SCALE = Bullet::BULLET_SCALE;
const int POWER = 200;
const int SPEED = ( int )( Bullet::BULLET_SCALE );

BulletShot::BulletShot( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_FIRE ) {
	_dir = dir.normalize( );
	_pos = pos + Vector( 0, 0, 1.0 ) * Bullet::BULLET_SCALE;
	_power = POWER * power;
	_speed = SPEED;
	_exist_time = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_ENEMY_ATTACK_FIRE_BALL );
}

BulletShot::~BulletShot( ) {
}


bool BulletShot::update( ) {
	// ˆÚ“®
	_exist_time++;
	if ( _exist_time < WAIT_TIME ) {
		return true;
	}
	if ( _exist_time >= WAIT_TIME + VANISH_TIME  ) {
		return false;
	}

	_pos += _dir * _speed;
	attackEnemy( _pos, _power );
	Effect effect;
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), _pos, _dir );
	return true;
}