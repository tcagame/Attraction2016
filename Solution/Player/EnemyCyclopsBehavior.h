#pragma once
#include "Behavior.h"

PTR( EnemyCyclopsBehavior );
PTR( Player );

class EnemyCyclopsBehavior : public Behavior {
public:
	EnemyCyclopsBehavior( );
	virtual ~EnemyCyclopsBehavior( );
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

