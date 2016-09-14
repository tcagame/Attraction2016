#pragma once

#include "Behavior.h"
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( PlayerBehavior );
PTR( Camera );

//コントローラーで動くもの
class PlayerBehavior : public Behavior {
public:
	enum PLAYER_STATE {
		PLAYER_STATE_WAIT,
		PLAYER_STATE_WALK,
		PLAYER_STATE_ATTACK,
		PLAYER_STATE_STORE,
		PLAYER_STATE_DEATHBLOW,
		PLAYER_STATE_DEAD,
	};
public:
	PlayerBehavior( unsigned char player_id, unsigned char player_controll_id );
	virtual ~PlayerBehavior( );
public:
	void update( );
	bool isDeathblow( );
protected:
	struct CONTROLL {
		Vector move;
		enum ACTION {
			NONE,
			ATTACK,
			DEATHBLOW,
			MUSTDEATHBLOW,
		} action;
	};
protected:
	virtual void attack( const CONTROLL& controll ) = 0;//攻撃などの外の行動
	void walk( const CONTROLL& controll );
	void pickupCrystal( const CONTROLL& controll );
	CONTROLL makeControll( );
protected:
	const int MAX_ATTACK_PATTERN;
	const int _player_id;
	const bool _controll;
	PLAYER_STATE _player_state;
	PLAYER_STATE _before_state;
	int _attack_pattern;
	bool _is_tutorial_sence;
};