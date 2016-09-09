#include "BulletBulletRain.h"
#include "App.h"
#include "Effect.h"

const int VANISH_TIME = 50;
const double BULLET_SCALE = 0.3;
const int POWER = 1;
const int SPEED = 1;

BulletBulletRain::BulletBulletRain( const Vector& pos, const Vector& dir )
: Bullet( Bullet::TYPE_BULLET_RAIN ) {
	_pos = pos + Vector( 0, 0, 0.5 );
	_dir = dir.normalize( );
	_power = POWER;
	_speed = SPEED;
	_exist_time = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_PLAYER_ATTACK_BULLET_RAIN );
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), pos, dir );
}

BulletBulletRain::~BulletBulletRain( ) {
}

bool BulletBulletRain::update( ) {
	//–¢ŽÀ‘•
	
	// ˆÚ“®
	_pos += _dir * _speed;
	_exist_time++;
	if ( _exist_time >= VANISH_TIME  ) {
		return false;
	}
	attackEnemy( _pos, POWER );
	Effect effect;
	effect.drawEffect( _effect_handle, Vector( BULLET_SCALE, BULLET_SCALE, BULLET_SCALE ), _pos, _dir );
	return true;
}