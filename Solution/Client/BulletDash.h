#pragma once
#include "Bullet.h"

PTR( BulletDash );

class BulletDash : public Bullet {
public:
	BulletDash( const Vector& pos, const Vector& dir );
	virtual ~BulletDash( );
public:
	virtual bool update( );
public:
	double getLength( ) const;
private:
	int _count;
};