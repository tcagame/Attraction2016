#pragma once
#include "Bullet.h"

PTR( BulletFire );

class BulletFire : public Bullet {
public:
	BulletFire( const Vector& pos, const Vector& dir );
	virtual ~BulletFire( );
public:
	virtual bool update( );
private:
	int _power;
	double _speed;
	int _exist_time;
};

