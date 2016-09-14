#pragma once
#include "Bullet.h"

PTR( BulletBubble );

class BulletBubble : public Bullet {
public:
	BulletBubble( const Vector& pos, const Vector& dir, int power );
	virtual ~BulletBubble( );
public:
	virtual bool update( );
private:
	Vector getBeginDir( ) const;
	Vector getEndDir( ) const;
private:
	double _ratio;
};

