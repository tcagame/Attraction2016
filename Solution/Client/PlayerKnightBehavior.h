#pragma once
#include "PlayerBehavior.h"
#include "smart_ptr.h"

PTR( PlayerKnightBehavior );

class PlayerKnightBehavior : public PlayerBehavior {
public:
	PlayerKnightBehavior( );
	virtual ~PlayerKnightBehavior( );
private:
	void attack( );
	void animationUpdate( );
};