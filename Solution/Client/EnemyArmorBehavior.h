#pragma once
#include "Behavior.h"
#include "smart_ptr.h"

PTR( EnemyArmorBehavior );
PTR( Player );


class EnemyArmorBehavior : public Behavior {
public:
	EnemyArmorBehavior( );
	virtual ~EnemyArmorBehavior( );
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