#pragma once
#include "Bullet.h"

PTR( BulletJab );

class BulletJab : public Bullet {
public:
	BulletJab( const Vector& pos, const Vector& dir );
	virtual ~BulletJab( );
public:
	virtual bool update( );
public:
	double getLength( ) const;
private:
	int _count;
};