#pragma once
#include "Behavior.h"
#include "smart_ptr.h"

PTR( EnemyGhostBehavior );
PTR( Player );

class EnemyGhostBehavior : public Behavior {
public:
	EnemyGhostBehavior( );
	virtual ~EnemyGhostBehavior( );
public:
	void update( );
private:
	void animationUpdate( );
	
	void movePosToTarget( );
	void switchStatus( );
private:
	PlayerWeakPtr _target;
	double _move_range;
	int _before_hp;
};

