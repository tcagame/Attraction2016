#pragma once
#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletStab );

class BulletStab : public Bullet {
public:
	BulletStab( const Vector& pos, double dir_x, double dir_y );
	virtual ~BulletStab( );
public:
	virtual bool update( );
private:
	Vector getPos( ) const;
	double getLength( ) const;
private:
	const Vector _pos;
	const Vector _dir;
private:
	double _ratio;
};