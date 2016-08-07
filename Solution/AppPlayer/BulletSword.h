#pragma once
#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletSword );

class BulletSword : public Bullet {
public:
	BulletSword( const Vector& pos, double dir_x, double dir_y );
	virtual ~BulletSword( );
public:
	virtual bool update( );
private:
	Vector getPos( ) const;
	Vector getBeginDir( ) const;
	Vector getEndDir( ) const;
	double getLength( ) const;

private:
	const Vector _pos;
	const Vector _dir;

private:
	double _ratio;
};

