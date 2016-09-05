#pragma once
#include "Behavior.h"

PTR( EnemyBossBehavior );
PTR( Player );

class EnemyBossBehavior : public Behavior {
public:
	EnemyBossBehavior( );
	virtual ~EnemyBossBehavior( );
public:
	enum  BOSS_ATTACK_PATTERN {
		BOSS_ATTACK_PATTERN_CLEAVE,	
		BOSS_ATTACK_PATTERN_BITE,
		BOSS_ATTACK_PATTERN_FIRE,	
		BOSS_ATTACK_PATTERN_BOMBING,
		BOSS_ATTACK_PATTERN_MAX,
	};							
public:						
	void update( );			
private:
	void animationUpdate( );	
	void movePosToTarget( );
	void switchStatus( );
	void onAttack( );
private:
	PlayerWeakPtr _target;
	double _attack_range[ BOSS_ATTACK_PATTERN_MAX ];
	int _befor_hp;
	bool _on_damage;
};