#pragma once

#include "Bullet.h"

PTR( BulletUpper );

class BulletUpper : public Bullet {
public:
	BulletUpper( const Vector& pos, const Vector& dir, int power );
	virtual ~BulletUpper( );
public:
	virtual bool update( );
public:
	double getLength( ) const;
private:
	int _count;
};

