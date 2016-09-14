#pragma once
#include "Bullet.h"

PTR( BulletShot );

class BulletShot : public Bullet {
public:
	BulletShot( const Vector& pos, const Vector& dir, int power );
	virtual ~BulletShot( );
public:
	virtual bool update( );
private:
	double _speed;
	int _exist_time;
};

