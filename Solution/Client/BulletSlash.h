#pragma once
#include "Bullet.h"
#include "mathmatics.h"

PTR( BulletSlash );

class BulletSlash : public Bullet {
public:
	BulletSlash( const Vector& pos, const Vector& dir, int power );
	virtual ~BulletSlash( );
public:
	virtual bool update( );
private:
	Vector getBeginDir( ) const;
	Vector getEndDir( ) const;
	double getLength( ) const;
private:
	double _ratio;
	bool _is_attack;
};