#pragma once
#include "Behavior.h"

PTR( EnemyBehavior );

class EnemyBehavior : public Behavior {
public:
	enum ENEMY_STATE {
		ENEMY_STATE_WAIT,
		ENEMY_STATE_WALK,
		ENEMY_STATE_ATTACK,
		ENEMY_STATE_DEAD,
	};
public:
	EnemyBehavior( );
	virtual ~EnemyBehavior( );
protected:
	ENEMY_STATE _enemy_state;
	ENEMY_STATE _before_state;
};