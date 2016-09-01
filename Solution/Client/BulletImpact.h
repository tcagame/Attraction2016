#pragma once

#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletImpact );

class BulletImpact : public Bullet {
public:
	static void initialize( );
public:
	BulletImpact( const Vector& pos, const Vector& dir );
	virtual ~BulletImpact( );
public:
	virtual bool update( );
public:
	Vector getPos( ) const;
	double getLength( ) const;
	int getAlpha( ) const;
private:
	Vector _pos;
	Vector _dir;
	int _count;
};
