#pragma once

#include "Bullet.h"

PTR( BulletImpact );

class BulletImpact : public Bullet {
public:
	BulletImpact( const Vector& pos, const Vector& dir );
	virtual ~BulletImpact( );
public:
	virtual bool update( );
public:
	double getLength( ) const;
private:
	int _count;
};
