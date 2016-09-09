#pragma once
#include "Bullet.h"

PTR( BulletBulletRain );

class BulletBulletRain : public Bullet {
public:
	BulletBulletRain( const Vector& pos, const Vector& dir );
	virtual ~BulletBulletRain( );
public:
	virtual bool update( );
private:
	int _power;
	double _speed;
	int _exist_time;
};