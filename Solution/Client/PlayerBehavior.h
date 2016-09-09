#pragma once
#include "Behavior.h"
#include "smart_ptr.h"


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
	PlayerBehavior( );
	virtual ~PlayerBehavior( );
public:
	void update( );
	//void pickupDeedBox( );
	//void pickupItem( );
	void pickupCrystal( );
protected:
	virtual void attack( ) = 0;//攻撃などの外の行動
protected:
	const int MAX_ATTACK_PATTERN;
	PLAYER_STATE _player_state;
	PLAYER_STATE _before_state;
	int _attack_pattern;
};