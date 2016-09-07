#pragma once
#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletFireBall );

class BulletFireBall : public Bullet {
public:
	void initialize( );
public:
	BulletFireBall( const Vector& pos, const Vector& dir );
	virtual ~BulletFireBall( );
public:
	virtual bool update( );
private:
	int _power;
	double _speed;
	int _exist_time;
};
