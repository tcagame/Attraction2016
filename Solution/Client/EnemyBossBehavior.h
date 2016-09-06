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
	enum BOSS_STATE {
		BOSS_STATE_ENTRY,
		BOSS_STATE_WAIT,
		BOSS_STATE_ATTACK,
		BOSS_STATE_DAMAGE,
		BOSS_STATE_DEAD,
	};
public:						
	void update( );			
private:
	void animationUpdate( );	
	void movePosToTarget( );
	void switchStatus( );
	void onAttack( int attack_pattern );
private:
	PlayerWeakPtr _target;
	BOSS_STATE _boss_state;
	BOSS_STATE _before_boss_state;
	double _attack_range[ BOSS_ATTACK_PATTERN_MAX ];
	int _befor_hp;
	bool _on_damage;
	bool _is_entry;
};