#pragma once
#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletStab );

class BulletStab : public Bullet {
public:
	BulletStab( const Vector& pos, const Vector& dir, int power );
	virtual ~BulletStab( );
public:
	virtual bool update( );
private:
	double getLength( ) const;
private:
	double _ratio;
};