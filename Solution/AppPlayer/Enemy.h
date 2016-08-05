#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( Enemy );
PTR( Player );

class Enemy {
public:
	enum STATUS {
		STATUS_WAIT,
		STATUS_WALK,
		STATUS_CLEAVE,
		STATUS_DAMAGE,
		STATUS_DEAD,
		STATUS_SMASH,
		STATUS_MAX
	};
public:
	Enemy( );
	virtual ~Enemy( );
public:
	void update( );
	Vector getPos( ) const;
	Vector getDir( ) const;
	double getAnimTime( ) const;
	STATUS getStatus( ) const;
private:
	void movePosToTarget( );
	void switchStatusOnRange( );
	void setStatus( STATUS status );
	void managementAnimationTimeOnStatus( );
	void onAttack( );
private:
	PlayerWeakPtr _target;
	Vector _pos;
	double _speed;
	Vector _dir;
	double _anim_time;
	STATUS _status;
	STATUS _before;
	double _move_range;
	double _attack_range;
	int _power;
	bool _is_attack;
};

