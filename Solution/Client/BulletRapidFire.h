#pragma once
#include "Bullet.h"

PTR( BulletRapidFire );

class BulletRapidFire : public Bullet {
public:
	BulletRapidFire( const Vector& pos, const Vector& dir, int power );
	virtual ~BulletRapidFire( );
public:
	virtual bool update( );
private:
	static const int BULLET_NUM = 2;
	Vector _bullet_pos[ BULLET_NUM ];
	int _bullet_effect_handle[ BULLET_NUM ];
	bool _exist_bullet[ BULLET_NUM ];
	double _speed;
	int _exist_time;
};
