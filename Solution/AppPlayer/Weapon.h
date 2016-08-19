#pragma once

#include "smart_ptr.h"
#include <array>

PTR( Weapon );
PTR( Bullet );

class Weapon {
public:
	static const int MAX_BULLET_NUM = 500;
public:
	Weapon( );
	virtual ~Weapon( );
public:
	virtual void update( );
	int getWeaponMaxNum( ) const;
	BulletPtr getBullet( int idx );

public:
	void add( BulletPtr bullet );
private:
	std::array< BulletPtr, MAX_BULLET_NUM > _bullet;
	int _weapon_max_num;
};

