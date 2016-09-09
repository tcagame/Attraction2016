#pragma once
#include "EnemyBehavior.h"

PTR( EnemyGoblinBehavior );
PTR( Player );

class EnemyGoblinBehavior : public EnemyBehavior {
public:
	EnemyGoblinBehavior( );
	virtual ~EnemyGoblinBehavior( );
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