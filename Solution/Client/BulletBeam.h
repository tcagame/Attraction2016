#pragma once
#include "Bullet.h"

PTR( BulletBeam );

class BulletBeam : public Bullet {
public:
	BulletBeam( const Vector& pos, const Vector& dir );
	virtual ~BulletBeam( );
public:
	virtual bool update( );
private:
	bool _show;
	bool _expired;
	double _radius;
	double _length;
	int _power;
};