#pragma once
#include "EnemyBehavior.h"

PTR( EnemyCyclopsBehavior );
PTR( Player );

class EnemyCyclopsBehavior : public EnemyBehavior {
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
	void searchTarget( );
private:
	PlayerWeakPtr _target;
	double _attack_range;
	double _move_range;
	int _befor_hp;
	bool _on_damage;
};

