#pragma once
#include "EnemyBehavior.h"
#include "smart_ptr.h"

PTR( EnemyGhostBehavior );
PTR( Player );

class EnemyGhostBehavior : public EnemyBehavior {
public:
	EnemyGhostBehavior( );
	virtual ~EnemyGhostBehavior( );
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
	double _move_range;
	double _attack_range;
	int _before_hp;
	bool _on_damage;
};

