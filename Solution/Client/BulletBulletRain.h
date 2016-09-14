#pragma once
#include "Bullet.h"

PTR( BulletBulletRain );

class BulletBulletRain : public Bullet {
public:
	BulletBulletRain( const Vector& pos, const Vector& dir, int power );
	virtual ~BulletBulletRain( );
public:
	virtual bool update( );
private:
	double _speed;
	int _exist_time;
};