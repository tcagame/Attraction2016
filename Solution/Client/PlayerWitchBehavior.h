#pragma once
#include "PlayerBehavior.h"

PTR( PlayerWitchBehavior );

class PlayerWitchBehavior : public PlayerBehavior {
public:
	PlayerWitchBehavior( unsigned char player_id );
	virtual ~PlayerWitchBehavior( );
private:
	void attack( const CONTROLL& controll );
	void animationUpdate( );
};

