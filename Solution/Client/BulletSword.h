#pragma once
#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletSword );

class BulletSword : public Bullet {
public:
	BulletSword( const Vector& pos, const Vector& dir, int power );
	virtual ~BulletSword( );
public:
	virtual bool update( );
private:
	Vector getBeginDir( ) const;
	Vector getEndDir( ) const;
	double getLength( ) const;
private:
	double _ratio;
};

