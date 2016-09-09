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
		BOSS_ATTACK_PATTERN_MAX,
	};	
	enum BOSS_STATE {
		BOSS_STATE_ENTRY,
		BOSS_STATE_WAIT,
		BOSS_STATE_FLY,
		BOSS_STATE_ATTACK,
		BOSS_STATE_BOMBING,
		BOSS_STATE_DAMAGE,
		BOSS_STATE_DESCENT,
		BOSS_STATE_DEAD,
	};
public:						
	void update( );			
private:
	void animationUpdate( );	
	void switchStatus( );
	void onAttack( int attack_pattern );
private:
	PlayerWeakPtr _target;
	BOSS_STATE _boss_state;
	BOSS_STATE _before_state;
	double _boss_damage_hp;
	double _attack_range[ BOSS_ATTACK_PATTERN_MAX ];
	bool _on_damage;
	bool _has_damage_motion;
	bool _has_entry;
	int _attack_pattern;
};