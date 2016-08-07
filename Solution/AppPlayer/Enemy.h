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
	int getHP( ) const;
	double getAnimTime( ) const;
	STATUS getStatus( ) const;
	void damage( int pow );
private:
	void movePosToTarget( );
	void switchStatusOnRange( );
	void setStatus( STATUS status );
	void managementAnimationTimeOnStatus( );
	void onAttack( );
private:
	Vector _pos;
	Vector _dir;
	int _power;
	int _hp;
	double _speed;
	
	STATUS _status;
	STATUS _before;

	PlayerWeakPtr _target;
	double _attack_range;
	double _move_range;
	
	bool _is_attack;
	bool _on_damege;
	
	double _anim_time;
};

