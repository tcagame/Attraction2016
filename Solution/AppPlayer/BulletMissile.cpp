#include "BulletMissile.h"
#include "Player.h"
#include "App.h"
#include "Framework.h"

const int VANISH_TIME = 300;

void BulletMissile::initialize( ) {
	FrameworkPtr fw = Framework::getInstance( );
	_power = 30;
	_speed = 0.3;
	_exist_time = 0;
}

BulletMissile::BulletMissile( const Vector& pos, const Vector& dir )
: Bullet( Bullet::MISSILE )
, _dir( dir.normalize( ) ) {
	_pos = pos;
	initialize( );
}

BulletMissile::~BulletMissile( ) {
}


bool BulletMissile::update( ) {
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
