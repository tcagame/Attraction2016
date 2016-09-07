#pragma once
#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletMissile );

class BulletMissile : public Bullet {
public:
	void initialize( );
public:
	BulletMissile( const Vector& pos, const Vector& dir );
	virtual ~BulletMissile( );
public:
	virtual bool update( );
private:
	int _power;
	double _speed;
	int _exist_time;
};
