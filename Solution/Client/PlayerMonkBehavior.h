#pragma once
#include "PlayerBehavior.h"
#include "smart_ptr.h"

PTR( PlayerMonkBehavior );

class PlayerMonkBehavior : public PlayerBehavior {
public:
	PlayerMonkBehavior( unsigned char player_id );
	virtual ~PlayerMonkBehavior( );
private:
	void attack( );
	void animationUpdate( );
private:
	CharacterWeakPtr _target;
};