#include "BulletExcalibur.h"
#include "App.h"
#include "Effect.h"

const int WAIT_TIME = 5;
const int VANISH_TIME = 20 + WAIT_TIME;
const double BULLET_SCALE = 0.3;
const int POWER = 500;
const int SPEED = 1;

BulletExcalibur::BulletExcalibur( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_EXCALIBUR ) {
	_pos = pos + Vector( 0, 0, 0.5 );
	_dir = dir.normalize( );
	_power = POWER;
	_speed = SPEED;
	_exist_time = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_EXCARIBUR );
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), pos, dir );
}

BulletExcalibur::~BulletExcalibur( ) {
}


bool BulletExcalibur::update( ) {
	_exist_time++;
	if ( _exist_time < WAIT_TIME ) {
		return true;
	}
	if ( _exist_time >= VANISH_TIME  ) {
		return false;
	}
	// ˆÚ“®
	_pos += _dir * _speed;
	attackEnemy( _pos, POWER );
	Effect effect;
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), _pos, _dir );
	return true;
}