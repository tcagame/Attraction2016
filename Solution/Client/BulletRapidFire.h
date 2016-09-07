#pragma once
#include "Bullet.h"

PTR( BulletRapidFire );

class BulletRapidFire : public Bullet {
public:
	BulletRapidFire( const Vector& pos, const Vector& dir );
	virtual ~BulletRapidFire( );
public:
	virtual bool update( );
private:
	static const int BULLET_NUM = 2;
	Vector _bullet_pos[ BULLET_NUM ];
	int _power;
	double _speed;
	int _exist_time;
};