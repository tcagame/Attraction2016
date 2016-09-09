#pragma once
#include "Bullet.h"

PTR( BulletRush );

class BulletRush : public Bullet {
public:
	BulletRush( const Vector& pos, const Vector& dir );
	virtual ~BulletRush( );
public:
	virtual bool update( );
public:
	double getLength( ) const;
private:
	int _count;
};