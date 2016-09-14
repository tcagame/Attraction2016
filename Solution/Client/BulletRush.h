#pragma once
#include "Bullet.h"
#include <array>

PTR( BulletRush );

class BulletRush : public Bullet {
public:
	static const int BLOW_NUM = 7;
public:
	BulletRush( const Vector& pos, const Vector& dir, int power );
	virtual ~BulletRush( );
public:
	virtual bool update( );
public:
	double getLength( ) const;
private:
	Vector _blow[ BLOW_NUM ];
	int _count;
};