#pragma once
#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletSplash );

class BulletSplash : public Bullet {
public:
	BulletSplash( const Vector& pos, const Vector& dir, int power );
	virtual ~BulletSplash( );
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
	double _time;
};
