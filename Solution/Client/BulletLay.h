#pragma once

#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletLay );

class BulletLay : public Bullet {
public:
	static void initialize( );
public:
	BulletLay( const Vector& pos, const Vector& dir );
	virtual ~BulletLay( );
public:
	virtual bool update( );
public:
	Vector getPos( ) const;
	Vector getDir( ) const;
	double getLength( ) const;
	double getRadius( ) const;
private:
	const Vector _pos;
	const Vector _dir;
private:
	bool _show;
	bool _expired;
	double _radius;
	double _length;
	static int _power;
	static int _cooltime;

};
