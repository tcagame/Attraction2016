#include "BulletFireBall.h"
#include "Player.h"
#include "Effect.h"
#include "App.h"

const int VANISH_TIME = 50;
const double EFFECT_SCALE = 1.0;

BulletFireBall::BulletFireBall( const Vector& pos, const Vector& dir, int power ) 
: Bullet( Bullet::TYPE_FIRE_BALL ) {
	_pos = pos;
	_dir = dir.normalize( );
	_power = power;
	_speed = 1;
	_exist_time = 0;
	Effect effect;
	_effect_handle = effect.setEffect( Effect::EFFECT_ENEMY_ATTACK_FIRE_BALL );
	effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), pos, dir );
}


BulletFireBall::~BulletFireBall( ) {
}

bool BulletFireBall::update( ) {
	// à⁄ìÆ
	_pos += _dir * _speed;
	_exist_time++;
	if ( _exist_time >= VANISH_TIME  ) {
		return false;
	}

	//çUåÇ
	AppPtr app = App::getTask( );

	for ( int i = 0; i < 4; i++ ) {
		PlayerPtr player = app->getPlayer( i );
		Vector player_pos = player->getPos( );
		Vector distance = _pos - player_pos;
		double length = distance.getLength( );
		Effect effect;
		effect.drawEffect( _effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), _pos, _dir );
		if ( length <= 1.0 ) {
			player->damage( _power );
			return false;
		}
	}
	return true;
}