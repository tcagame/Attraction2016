#include "BulletFireBall.h"
#include "Player.h"
#include "App.h"

const int VANISH_TIME = 50;

void BulletFireBall::initialize( ) {
	_power = 100;
	_speed = 1;
	_exist_time = 0;
}


BulletFireBall::BulletFireBall( const Vector& pos, const Vector& dir ) 
: Bullet( Bullet::TYPE_FIRE_BALL )
, _dir( dir.normalize( ) ) {
	_pos = pos;
	initialize( );
}


BulletFireBall::~BulletFireBall( ) {
}

bool BulletFireBall::update( ) {
	// ˆÚ“®
	_pos += _dir * _speed;


	_exist_time++;
	if ( _exist_time >= VANISH_TIME  ) {
		return false;
	}

	//UŒ‚
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );
	Vector player_pos = player->getPos( );
	Vector distance = _pos - player_pos;
	double length = distance.getLength( );
	if ( length <= 1.0 ) {
		player->damage( _power );
		return false;
	}
	return true;
}