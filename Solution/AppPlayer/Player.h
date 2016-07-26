#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( Player );

class Player {
public:
	enum STATUS {
		STATUS_WAIT,
		STATUS_WALK,
		STATUS_ATTACK,
		STATUS_DAMAGE,
		STATUS_DEAD,
		STATUS_USE,
		STATUS_MAX
	};
public:
	Player( );
	virtual ~Player( );
public:
	void update( );
	Vector getPos( ) const;
	Vector getDir( ) const;
	int getAnimTime( ) const;
	STATUS getStatus( ) const;
private:

private:
	Vector _pos;
	double _speed;
	Vector _dir;
	int _anim_time;
	STATUS _status;
};

