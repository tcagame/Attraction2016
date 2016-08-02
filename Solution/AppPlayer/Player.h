#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( Player );
PTR( Camera );

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
	Player( CameraConstPtr camera );
	virtual ~Player( );
public:
	void update( );
	void setPos( const Vector& pos );
	Vector getPos( ) const;
	Vector getDir( ) const;
	int getAnimTime( ) const;
	STATUS getStatus( ) const;
	bool getExistence( ) const;
private:
	CameraConstPtr _camera;
	bool is_attack;
	bool _is_existence;
	Vector _pos;
	double _speed;
	Vector _dir;
	int _anim_time;
	STATUS _status;
};

