#pragma once
#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletSlash );

class BulletSlash : public Bullet {
public:
	BulletSlash( const Vector& pos, double dir_x, double dir_y );
	virtual ~BulletSlash( );
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
	bool _is_attack;
};