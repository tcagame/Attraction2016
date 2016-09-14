#include "BulletFire.h"
#include "App.h"
#include "Effect.h"

const int VANISH_TIME = 20;
const double BULLET_SCALE = 0.3;
const int POWER = 1;
const double SPEED = 1;

BulletFire::BulletFire( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_FIRE ) {
	_pos = pos + Vector( 0, 0, 0.5 );
	_dir = dir.normalize( );
	_power = POWER * power;
	_speed = SPEED;
	_exist_time = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_ENEMY_ATTACK_FIRE_BALL );
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), pos, dir );
}

BulletFire::~BulletFire( ) {
}


bool BulletFire::update( ) {
	// ˆÚ“®
	_exist_time++;
	if ( _exist_time >= VANISH_TIME  ) {
		return false;
	}
	_pos += _dir * _speed;
	attackEnemy( _pos, _power );
	Effect effect;
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), _pos, _dir );
	return true;
}