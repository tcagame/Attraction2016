#pragma once
#include "Bullet.h"

PTR( BulletSmash );

class BulletSmash : public Bullet {
public:
	BulletSmash( const Vector& pos, const Vector& dir, int power );
	virtual ~BulletSmash( );
public:
	virtual bool update( );
private:
	double _speed;
	int _exist_time;
};