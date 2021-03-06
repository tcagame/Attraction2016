#pragma once
#include "Behavior.h"
#include "mathmatics.h"

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
	bool isDead( );
private:
	void animationUpdate( );	
	void switchStatus( );
	void onAttack( int attack_pattern );
	void searchTarget( );
private:
	PlayerWeakPtr _target;
	BOSS_STATE _boss_state;
	BOSS_STATE _before_state;
	bool _is_dead;
	Vector _target_pos; 
	double _boss_damage_hp;
	int _boss_fly_time;
	double _attack_range[ BOSS_ATTACK_PATTERN_MAX ];
	bool _has_entry;
	int _attack_pattern;
	int _clear_time;
	bool _is_clear;
};