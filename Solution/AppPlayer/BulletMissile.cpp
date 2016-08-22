#include "BulletMissile.h"
#include "Framework.h"
#include "Player.h"


void BulletMissile::initialize( ) {
	FrameworkPtr fw = Framework::getInstance( );
	_power = 1;
	_speed = 1.0;
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
	// �ړ�
	_pos += _dir * _speed;

	return true;
}
