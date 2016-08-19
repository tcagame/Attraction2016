#include "Weapon.h"
#include "Bullet.h"
#include "BulletSword.h"
#include "Framework.h"


Weapon::Weapon( ) {
	_weapon_max_num = 0;
}


Weapon::~Weapon( ) {
}

void Weapon::update( ) {
	for ( int i = 0; i < MAX_BULLET_NUM; i++ ) {
		BulletPtr bullet = _bullet[ i ];
		if ( !bullet ) {
			continue;
		}
		_bullet[ i ]->update( );
	}
}

int Weapon::getWeaponMaxNum( ) const {
	return _weapon_max_num;
}

BulletPtr Weapon::getBullet( int idx ) {
	return _bullet[ idx ];
}

void Weapon::add( BulletPtr bullet ) {
	for ( int i = 0; i < MAX_BULLET_NUM; i++ ) {
		BulletPtr check = _bullet[ i ];
		if ( !check ) {
			_bullet[ i ] = bullet;
			_weapon_max_num++;
			break;
		}
	}
}