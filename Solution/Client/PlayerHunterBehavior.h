#pragma once
#include "PlayerBehavior.h"
#include "smart_ptr.h"

PTR( PlayerHunterBehavior );

class PlayerHunterBehavior : public PlayerBehavior {
public:
	PlayerHunterBehavior( );
	virtual ~PlayerHunterBehavior( );
private:
	void otherAction( );
	void animationUpdate( );
};

