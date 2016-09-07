#pragma once
#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletLay );

class BulletLay : public Bullet {
public:
	BulletLay( const Vector& pos, const Vector& dir );
	virtual ~BulletLay( );
public:
	virtual bool update( );
public:
	double getLength( ) const;
	double getRadius( ) const;
private:
	bool _show;
	bool _expired;
	double _radius;
	double _length;
	int _power;
};
