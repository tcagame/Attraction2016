#pragma once
#include "PlayerBehavior.h"
#include "smart_ptr.h"

PTR( PlayerKnightBehavior );

class PlayerKnightBehavior : public PlayerBehavior {
public:
	PlayerKnightBehavior( unsigned char player_id );
	virtual ~PlayerKnightBehavior( );
private:
	void attack( const CONTROLL& controll );
	void animationUpdate( );
};

