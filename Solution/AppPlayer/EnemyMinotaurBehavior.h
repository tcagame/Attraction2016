#pragma once
#include "Behavior.h"
#include "smart_ptr.h"

PTR( EnemyMinotaurBehavior );
PTR( Player );

class EnemyMinotaurBehavior : public Behavior {
public:
	EnemyMinotaurBehavior( );
	virtual ~EnemyMinotaurBehavior( );
public:
	void update( );
private:
	void animationUpdate( );
	
	void movePosToTarget( );
	void switchStatus( );
	void onAttack( );
private:
	PlayerWeakPtr _target;
	double _attack_range;
	double _move_range;
	int _befor_hp;
	bool _on_damage;
};

