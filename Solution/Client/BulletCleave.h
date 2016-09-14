#pragma once
#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletCleave );

class BulletCleave : public Bullet {
public:
	BulletCleave( const Vector& pos, double dir_x, double dir_y );
	virtual ~BulletCleave( );
public:
	virtual bool update( );
private:
	Vector getBeginDir( ) const;
	Vector getEndDir( ) const;
	double getLength( ) const;
private:
	double _ratio;
};
