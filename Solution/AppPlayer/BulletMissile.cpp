#include "BulletMissile.h"
#include "Framework.h"
#include "Player.h"


void BulletMissile::initialize( ) {
	FrameworkPtr fw = Framework::getInstance( );
	_power = 1.0;
	_speed = 1.0;
}

BulletMissile::BulletMissile( const Vector& pos, const Vector& dir )
: Bullet( Bullet::MISSILE )
, _dir( dir.normalize( ) ) {
	_pos = pos;
}

BulletMissile::~BulletMissile( ) {
}


bool BulletMissile::update( ) {
	// ˆÚ“®
	_pos += _dir * _speed;

	return true;
}
