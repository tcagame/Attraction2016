#pragma once
#include "Bullet.h"

PTR( BulletSmash );

class BulletSmash : public Bullet {
public:
	BulletSmash( const Vector& pos, const Vector& dir );
	virtual ~BulletSmash( );
public:
	virtual bool update( );
private:
	int _power;
	double _speed;
	int _exist_time;
};