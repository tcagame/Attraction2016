#pragma once
#include "Bullet.h"

PTR( BulletExcalibur );

class BulletExcalibur : public Bullet {
public:
	BulletExcalibur( const Vector& pos, const Vector& dir );
	virtual ~BulletExcalibur( );
public:
	virtual bool update( );
private:
	int _power;
	double _speed;
	int _exist_time;
};

