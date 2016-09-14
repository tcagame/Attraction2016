#pragma once
#include "Bullet.h"

PTR( BulletExcalibur );

class BulletExcalibur : public Bullet {
public:
	BulletExcalibur( const Vector& pos, const Vector& dir, int power );
	virtual ~BulletExcalibur( );
public:
	virtual bool update( );
private:
	int _exist_time;
};

