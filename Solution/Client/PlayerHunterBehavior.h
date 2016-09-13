#pragma once
#include "PlayerBehavior.h"
#include "smart_ptr.h"

PTR( PlayerHunterBehavior );

class PlayerHunterBehavior : public PlayerBehavior {
public:
	PlayerHunterBehavior( unsigned char player_id );
	virtual ~PlayerHunterBehavior( );
private:
	void attack( );
	void animationUpdate( );
};

