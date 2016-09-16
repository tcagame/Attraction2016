#pragma once
#include "EnemyBehavior.h"
#include "smart_ptr.h"

PTR( EnemyArmorBehavior );
PTR( Player );


class EnemyArmorBehavior : public EnemyBehavior {
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
	void searchTarget( );
private:
	PlayerWeakPtr _target;
	double _attack_range;
	double _move_range;
	int _befor_hp;
	bool _on_damage;
};